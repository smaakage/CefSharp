// Copyright � 2010-2015 The CefSharp Authors. All rights reserved.
//
// Use of this source code is governed by a BSD-style license that can be found in the LICENSE file.

#pragma once

#include "Stdafx.h"

#include "include\cef_callback.h"
#include "CefWrapper.h"

namespace CefSharp
{
    namespace Internals
    {
        public ref class CefCallbackWrapper : public ICallback, public CefWrapper
        {
        private:
            MCefRefPtr<CefCallback> _callback;

        public:
            CefCallbackWrapper(CefRefPtr<CefCallback> &callback) :
                _callback(callback)
            {
            
            }

            !CefCallbackWrapper()
            {
                _callback = NULL;
            }

            ~CefCallbackWrapper()
            {
                this->!CefCallbackWrapper();

                _disposed = true;
            }

            virtual void Cancel()
            {
                ThrowIfDisposed();

                _callback->Cancel();
            }

            virtual void Continue()
            {
                ThrowIfDisposed();

                _callback->Continue();

                // Do not self-dispose here or in Cancel because ResourceHandlerWrapper
                // already has a reference to this callback and will take care
                // of its disposal.  See GitHub issue #1143 for a repro of an
                // AccessViolationException caused by self-disposal.
            }
        };
    }
}