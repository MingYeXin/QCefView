#include "CCefClientDelegate.h"

#include <QDebug>
#include <QScreen>

#include "QCefViewPrivate.h"
#include "utils/ValueConvertor.h"

CCefClientDelegate::CCefClientDelegate(QSharedPointer<QCefViewPrivate> p)
  : pCefViewPrivate_(p)
{
  pendingDownloadItemMap_.clear();
  confirmedDownloadItemMap_.clear();
  pendingJSDialogMap_.clear();
}

CCefClientDelegate::~CCefClientDelegate()
{
  qDebug() << "CCefClientDelegate is being destructed";

  clearJSDialogMap();
}

void
CCefClientDelegate::clearJSDialogMap()
{
  /// Called to cancel any pending dialogs and reset any saved dialog state.
  /// Will be called due to events like page navigation irregardless of whether
  /// any dialogs are currently pending.

  for (auto dlg : pendingJSDialogMap_) {
    if (dlg) {
      dlg->reject();
    }
  }
  pendingJSDialogMap_.clear();
}

void
CCefClientDelegate::processUrlRequest(CefRefPtr<CefBrowser>& browser, CefRefPtr<CefFrame>& frame, const CefString& url)
{
  AcquireAndValidateCefViewPrivate(pCefViewPrivate);

  auto b = browser->GetIdentifier();
  auto f = ValueConvertor::FrameIdC2Q(frame->GetIdentifier());
  auto u = QString::fromStdString(url);

  runInMainThread([pCefViewPrivate, b, f, u]() {
    if (pCefViewPrivate->q_ptr) {
      emit pCefViewPrivate->q_ptr->cefUrlRequest(b, f, u);
    }
  });
}

void
CCefClientDelegate::processQueryRequest(CefRefPtr<CefBrowser>& browser,
                                        CefRefPtr<CefFrame>& frame,
                                        const CefString& request,
                                        const int64_t query_id)
{
  AcquireAndValidateCefViewPrivate(pCefViewPrivate);

  auto b = browser->GetIdentifier();
  auto f = ValueConvertor::FrameIdC2Q(frame->GetIdentifier());
  auto r = QString::fromStdString(request);
  auto q = pCefViewPrivate->createQuery(r, query_id);

  runInMainThread([pCefViewPrivate, b, f, q]() {
    if (pCefViewPrivate->q_ptr) {
      emit pCefViewPrivate->q_ptr->cefQueryRequest(b, f, q);
    }
  });
}

void
CCefClientDelegate::focusedEditableNodeChanged(CefRefPtr<CefBrowser>& browser,
                                               CefRefPtr<CefFrame>& frame,
                                               bool focusOnEditableNode)
{
  AcquireAndValidateCefViewPrivate(pCefViewPrivate);

  runInMainThread(                             //
    [pCefViewPrivate, focusOnEditableNode]() { //
      pCefViewPrivate->onCefInputStateChanged(focusOnEditableNode);
    });
}

void
CCefClientDelegate::invokeMethodNotify(CefRefPtr<CefBrowser>& browser,
                                       CefRefPtr<CefFrame>& frame,
                                       const CefString& method,
                                       const CefRefPtr<CefListValue>& arguments)
{
  AcquireAndValidateCefViewPrivate(pCefViewPrivate);

  auto b = browser->GetIdentifier();
  auto f = ValueConvertor::FrameIdC2Q(frame->GetIdentifier());
  QVariantList args;
  for (int i = 0; i < arguments->GetSize(); i++) {
    QVariant qV;
    auto cV = arguments->GetValue(i);
    ValueConvertor::CefValueToQVariant(&qV, cV.get());
    args.push_back(qV);
  }
  auto m = QString::fromStdString(method);

  runInMainThread([pCefViewPrivate, b, f, m, args]() {
    if (pCefViewPrivate->q_ptr) {
      emit pCefViewPrivate->q_ptr->invokeMethod(b, f, m, args);
    }
  });
}

void
CCefClientDelegate::reportJSResult(CefRefPtr<CefBrowser>& browser,
                                   CefRefPtr<CefFrame>& frame,
                                   const CefString& context,
                                   const CefRefPtr<CefValue>& result)
{
  AcquireAndValidateCefViewPrivate(pCefViewPrivate);

  auto b = browser->GetIdentifier();
  auto f = ValueConvertor::FrameIdC2Q(frame->GetIdentifier());
  QVariant qV;
  ValueConvertor::CefValueToQVariant(&qV, result.get());
  auto c = QString::fromStdString(context);

  runInMainThread([pCefViewPrivate, b, f, c, qV]() {
    if (pCefViewPrivate->q_ptr) {
      emit pCefViewPrivate->q_ptr->reportJavascriptResult(b, f, c, qV);
    }
  });
}
