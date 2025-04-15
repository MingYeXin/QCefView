#include "details/CCefClientDelegate.h"

#include "details/QCefViewPrivate.h"

#include <QDebug>

void
CCefClientDelegate::loadingStateChanged(CefRefPtr<CefBrowser>& browser,
                                        bool isLoading,
                                        bool canGoBack,
                                        bool canGoForward)
{
  if (!IsValidBrowser(browser)) {
    bool pCefViewPrivateIsNull = true;
    if (pCefViewPrivate_) {
      pCefViewPrivateIsNull = false;
    }
    bool CefBrowserIsNull = true;
    if (!pCefViewPrivateIsNull && pCefViewPrivate_->pCefBrowser_) {
      CefBrowserIsNull = false;
    }
    bool browserIsSame = false;
    if (!pCefViewPrivateIsNull && !CefBrowserIsNull) {
      browserIsSame = browser->IsSame(pCefViewPrivate_->pCefBrowser_);
    }
    qDebug() << "CCefClientDelegate::loadingStateChanged"
             << QString("pCefViewPrivate_(%1), pCefViewPrivate_->pCefBrowser_(%2), browser->IsSame(%3)")
                  .arg(pCefViewPrivateIsNull)
                  .arg(CefBrowserIsNull)
                  .arg(browserIsSame);
    if (pCefViewPrivate_) {
      emit pCefViewPrivate_->q_ptr->loadingStateChangedBeforeCefBrowserCreate();
    }
    return;
  }

  emit pCefViewPrivate_->q_ptr->loadingStateChanged(browser->GetIdentifier(), isLoading, canGoBack, canGoForward);
}

void
CCefClientDelegate::loadStart(CefRefPtr<CefBrowser>& browser, CefRefPtr<CefFrame>& frame, int transitionType)
{
  if (!IsValidBrowser(browser)) {
    bool pCefViewPrivateIsNull = true;
    if (pCefViewPrivate_) {
      pCefViewPrivateIsNull = false;
    }
    bool CefBrowserIsNull = true;
    if (!pCefViewPrivateIsNull && pCefViewPrivate_->pCefBrowser_) {
      CefBrowserIsNull = false;
    }
    bool browserIsSame = false;
    if (!pCefViewPrivateIsNull && !CefBrowserIsNull) {
      browserIsSame = browser->IsSame(pCefViewPrivate_->pCefBrowser_);
    }
    qDebug() << "CCefClientDelegate::loadStart"
             << QString("pCefViewPrivate_(%1), pCefViewPrivate_->pCefBrowser_(%2), browser->IsSame(%3)")
                  .arg(pCefViewPrivateIsNull)
                  .arg(CefBrowserIsNull)
                  .arg(browserIsSame);
    if (pCefViewPrivate_) {
      emit pCefViewPrivate_->q_ptr->loadStartBeforeCefBrowserCreate();
    }
    return;
  }

  emit pCefViewPrivate_->q_ptr->loadStart(
    browser->GetIdentifier(), ValueConvertor::FrameIdC2Q(frame->GetIdentifier()), frame->IsMain(), transitionType);
}

void
CCefClientDelegate::loadEnd(CefRefPtr<CefBrowser>& browser, CefRefPtr<CefFrame>& frame, int httpStatusCode)
{
  if (!IsValidBrowser(browser)) {
    bool pCefViewPrivateIsNull = true;
    if (pCefViewPrivate_) {
      pCefViewPrivateIsNull = false;
    }
    bool CefBrowserIsNull = true;
    if (!pCefViewPrivateIsNull && pCefViewPrivate_->pCefBrowser_) {
      CefBrowserIsNull = false;
    }
    bool browserIsSame = false;
    if (!pCefViewPrivateIsNull && !CefBrowserIsNull) {
      browserIsSame = browser->IsSame(pCefViewPrivate_->pCefBrowser_);
    }
    qDebug() << "CCefClientDelegate::loadEnd"
             << QString("pCefViewPrivate_(%1), pCefViewPrivate_->pCefBrowser_(%2), browser->IsSame(%3)")
                  .arg(pCefViewPrivateIsNull)
                  .arg(CefBrowserIsNull)
                  .arg(browserIsSame);
    if (pCefViewPrivate_) {
      emit pCefViewPrivate_->q_ptr->loadEndBeforeCefBrowserCreate();
    }
    return;
  }

  // workaround for:
  // https://github.com/chromiumembedded/cef/issues/3870
  // after navigation CEF resets the browser focus status
  // without any callback notification (AKA, released the
  // focus silently), so we need to update the CEF browser
  // focus status according to the one we have kept
  if (true                                     //
      && pCefViewPrivate_->isOSRModeEnabled_   //
      && pCefViewPrivate_->osr.hasCefGotFocus_ //
      && browser->GetHost()                    //
  ) {
    browser->GetHost()->SetFocus(true);
  }

  emit pCefViewPrivate_->q_ptr->loadEnd(
    browser->GetIdentifier(), ValueConvertor::FrameIdC2Q(frame->GetIdentifier()), frame->IsMain(), httpStatusCode);
}

void
CCefClientDelegate::loadError(CefRefPtr<CefBrowser>& browser,
                              CefRefPtr<CefFrame>& frame,
                              int errorCode,
                              const CefString& errorMsg,
                              const CefString& failedUrl,
                              bool& handled)
{
  if (!IsValidBrowser(browser)) {
    bool pCefViewPrivateIsNull = true;
    if (pCefViewPrivate_) {
      pCefViewPrivateIsNull = false;
    }
    bool CefBrowserIsNull = true;
    if (!pCefViewPrivateIsNull && pCefViewPrivate_->pCefBrowser_) {
      CefBrowserIsNull = false;
    }
    bool browserIsSame = false;
    if (!pCefViewPrivateIsNull && !CefBrowserIsNull) {
      browserIsSame = browser->IsSame(pCefViewPrivate_->pCefBrowser_);
    }
    qDebug() << "CCefClientDelegate::loadError"
             << QString("pCefViewPrivate_(%1), pCefViewPrivate_->pCefBrowser_(%2), browser->IsSame(%3)")
                  .arg(pCefViewPrivateIsNull)
                  .arg(CefBrowserIsNull)
                  .arg(browserIsSame);
    if (pCefViewPrivate_) {
      emit pCefViewPrivate_->q_ptr->loadErrorBeforeCefBrowserCreate();
    }
    return;
  }

  handled = pCefViewPrivate_->handleLoadError(browser, frame, errorCode, errorMsg, failedUrl);
}
