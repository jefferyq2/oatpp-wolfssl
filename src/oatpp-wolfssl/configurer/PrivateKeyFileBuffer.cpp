/***************************************************************************
 *
 * Project         _____    __   ____   _      _
 *                (  _  )  /__\ (_  _)_| |_  _| |_
 *                 )(_)(  /(__)\  )( (_   _)(_   _)
 *                (_____)(__)(__)(__)  |_|    |_|
 *
 *
 * Copyright 2018-present, Leonid Stryzhevskyi <lganzzzo@gmail.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 ***************************************************************************/

#include "PrivateKeyFileBuffer.hpp"

namespace oatpp { namespace wolfssl { namespace configurer {

PrivateKeyFileBuffer::PrivateKeyFileBuffer(const oatpp::String &fileBuffer, int filetype)
  : m_fileBuffer(fileBuffer)
  , m_fileType(filetype)
{}

void PrivateKeyFileBuffer::configure(WOLFSSL_CTX *ctx) {
  if(!m_fileBuffer->empty()) {
    auto ret = wolfSSL_CTX_use_PrivateKey_buffer(ctx, (const unsigned char *) m_fileBuffer->data(), m_fileBuffer->size() + 1, m_fileType);
    if(ret != WOLFSSL_SUCCESS) {
      OATPP_LOGD("[oatpp::wolfssl::configurer::PrivateKeyFileBuffer::configure()]", "Error. Call to wolfSSL_CTX_use_PrivateKey_buffer, return value=%d", ret);
      throw std::runtime_error("[oatpp::wolfssl::configurer::PrivateKeyFileBuffer::configure()]: Error. Can't parse privateKey");
    }
  }
}

}}}
