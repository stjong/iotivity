//******************************************************************
//
// Copyright 2016 Samsung Electronics All Rights Reserved.
//
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

#ifndef _NS_PROVIDER_CACHEADAPTER__H_
#define _NS_PROVIDER_CACHEADAPTER__H_

#include <pthread.h>
#include <stdbool.h>

#include "NSCommon.h"
#include "NSConstants.h"
#include "NSStructs.h"
#include "oic_malloc.h"
#include "oic_string.h"
#include "NSStorageAdapter.h"
#include "NSUtil.h"

NSResult NSProviderDeleteCacheData(NSCacheType, void *);

bool NSProviderCompareIdCacheData(NSCacheType, void *, const char *);

bool NSProviderIsFoundCacheData(NSCacheType, void *, void*);

NSResult NSCacheUpdateSubScriptionState(NSCacheList *, char *, bool);

NSResult NSProviderDeleteSubDataFromObId(NSCacheList * list, OCObservationId id);

pthread_mutex_t NSCacheMutex;
pthread_mutexattr_t NSCacheMutexAttr;

#endif /* _NS_PROVIDER_CACHEADAPTER__H_ */
