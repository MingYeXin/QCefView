#include "details/CCefClientDelegate.h"

#include "details/QCefViewPrivate.h"

#include <QDebug>

void
CCefClientDelegate::loadingStateChanged(CefRefPtr<CefBrowser>& browser,
                                        bool isLoading,
                                        bool canGoBack,
                                        bool canGoForward)
{
#if 0
  AcquireAndValidateCefViewPrivate(pCefViewPrivate);
#else
  auto pCefViewPrivate = pCefViewPrivate_.lock();
  if (!pCefViewPrivate || !pCefViewPrivate->pCefBrowser_ || !browser->IsSame(pCefViewPrivate->pCefBrowser_)) {
    bool pCefViewPrivateIsNull = true;
    if (pCefViewPrivate) {
      pCefViewPrivateIsNull = false;
    }
    bool CefBrowserIsNull = true;
    if (!pCefViewPrivateIsNull && pCefViewPrivate->pCefBrowser_) {
      CefBrowserIsNull = false;
    }
    bool browserIsSame = false;
    if (!pCefViewPrivateIsNull && !CefBrowserIsNull) {
      browserIsSame = browser->IsSame(pCefViewPrivate->pCefBrowser_);
    }
    qDebug() << "CCefClientDelegate::loadingStateChanged"
             << QString("pCefViewPrivate_(%1), pCefViewPrivate_->pCefBrowser_(%2), browser->IsSame(%3)")
                  .arg(pCefViewPrivateIsNull)
                  .arg(CefBrowserIsNull)
                  .arg(browserIsSame);
    if (pCefViewPrivate && pCefViewPrivate->q_ptr) {
      emit pCefViewPrivate->q_ptr->loadingStateChangedBeforeCefBrowserCreate();
    }
    return;
  }
#endif

  runInMainThread([=]() {
    if (pCefViewPrivate->q_ptr) {
      emit pCefViewPrivate->q_ptr->loadingStateChanged(browser->GetIdentifier(), isLoading, canGoBack, canGoForward);
    }
  });
}

void
CCefClientDelegate::loadStart(CefRefPtr<CefBrowser>& browser, CefRefPtr<CefFrame>& frame, int transitionType)
{
#if 0
  AcquireAndValidateCefViewPrivate(pCefViewPrivate);
#else
  auto pCefViewPrivate = pCefViewPrivate_.lock();
  if (!pCefViewPrivate || !pCefViewPrivate->pCefBrowser_ || !browser->IsSame(pCefViewPrivate->pCefBrowser_)) {
    bool pCefViewPrivateIsNull = true;
    if (pCefViewPrivate) {
      pCefViewPrivateIsNull = false;
    }
    bool CefBrowserIsNull = true;
    if (!pCefViewPrivateIsNull && pCefViewPrivate->pCefBrowser_) {
      CefBrowserIsNull = false;
    }
    bool browserIsSame = false;
    if (!pCefViewPrivateIsNull && !CefBrowserIsNull) {
      browserIsSame = browser->IsSame(pCefViewPrivate->pCefBrowser_);
    }
    qDebug() << "CCefClientDelegate::loadStart"
             << QString("pCefViewPrivate_(%1), pCefViewPrivate_->pCefBrowser_(%2), browser->IsSame(%3)")
                  .arg(pCefViewPrivateIsNull)
                  .arg(CefBrowserIsNull)
                  .arg(browserIsSame);
    if (pCefViewPrivate && pCefViewPrivate->q_ptr) {
      emit pCefViewPrivate->q_ptr->loadStartBeforeCefBrowserCreate();
    }
    return;
  }
#endif

  runInMainThread([=]() {
    if (pCefViewPrivate->q_ptr) {
      emit pCefViewPrivate->q_ptr->loadStart(
        browser->GetIdentifier(), ValueConvertor::FrameIdC2Q(frame->GetIdentifier()), frame->IsMain(), transitionType);
    }
  });
}

void
CCefClientDelegate::loadEnd(CefRefPtr<CefBrowser>& browser, CefRefPtr<CefFrame>& frame, int httpStatusCode)
{
#if 0
  AcquireAndValidateCefViewPrivate(pCefViewPrivate);
#else
  auto pCefViewPrivate = pCefViewPrivate_.lock();
  if (!pCefViewPrivate || !pCefViewPrivate->pCefBrowser_ || !browser->IsSame(pCefViewPrivate->pCefBrowser_)) {
    bool pCefViewPrivateIsNull = true;
    if (pCefViewPrivate) {
      pCefViewPrivateIsNull = false;
    }
    bool CefBrowserIsNull = true;
    if (!pCefViewPrivateIsNull && pCefViewPrivate->pCefBrowser_) {
      CefBrowserIsNull = false;
    }
    bool browserIsSame = false;
    if (!pCefViewPrivateIsNull && !CefBrowserIsNull) {
      browserIsSame = browser->IsSame(pCefViewPrivate->pCefBrowser_);
    }
    qDebug() << "CCefClientDelegate::loadEnd"
             << QString("pCefViewPrivate_(%1), pCefViewPrivate_->pCefBrowser_(%2), browser->IsSame(%3)")
                  .arg(pCefViewPrivateIsNull)
                  .arg(CefBrowserIsNull)
                  .arg(browserIsSame);
    if (pCefViewPrivate && pCefViewPrivate->q_ptr) {
      emit pCefViewPrivate->q_ptr->loadEndBeforeCefBrowserCreate();
    }
    return;
  }
#endif

  runInMainThread([=]() {
    if (pCefViewPrivate->q_ptr) {
      emit pCefViewPrivate->q_ptr->loadEnd(
        browser->GetIdentifier(), ValueConvertor::FrameIdC2Q(frame->GetIdentifier()), frame->IsMain(), httpStatusCode);
    }
  });
}

void
CCefClientDelegate::loadError(CefRefPtr<CefBrowser>& browser,
                              CefRefPtr<CefFrame>& frame,
                              int errorCode,
                              const CefString& errorMsg,
                              const CefString& failedUrl,
                              bool& handled)
{
#if 0
  AcquireAndValidateCefViewPrivate(pCefViewPrivate);
#else
  auto pCefViewPrivate = pCefViewPrivate_.lock();
  if (!pCefViewPrivate || !pCefViewPrivate->pCefBrowser_ || !browser->IsSame(pCefViewPrivate->pCefBrowser_)) {
    bool pCefViewPrivateIsNull = true;
    if (pCefViewPrivate) {
      pCefViewPrivateIsNull = false;
    }
    bool CefBrowserIsNull = true;
    if (!pCefViewPrivateIsNull && pCefViewPrivate->pCefBrowser_) {
      CefBrowserIsNull = false;
    }
    bool browserIsSame = false;
    if (!pCefViewPrivateIsNull && !CefBrowserIsNull) {
      browserIsSame = browser->IsSame(pCefViewPrivate->pCefBrowser_);
    }
    qDebug() << "CCefClientDelegate::loadError"
             << QString("pCefViewPrivate_(%1), pCefViewPrivate_->pCefBrowser_(%2), browser->IsSame(%3)")
                  .arg(pCefViewPrivateIsNull)
                  .arg(CefBrowserIsNull)
                  .arg(browserIsSame);
    if (pCefViewPrivate && pCefViewPrivate->q_ptr) {
      emit pCefViewPrivate->q_ptr->loadErrorBeforeCefBrowserCreate();
    }
    return;
  }
#endif

  runInMainThreadAndWait([&]() {
    if (pCefViewPrivate->q_ptr) {
      handled = pCefViewPrivate->handleLoadError(browser, frame, errorCode, errorMsg, failedUrl);
    }
  });
}
