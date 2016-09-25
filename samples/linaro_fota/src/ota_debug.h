/*
 * Copyright (c) 2016 Linaro Limited
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
 */

#include <misc/printk.h>

#define DEBUG

#define OTA_INFO(fmt, ...) printk("ota: " fmt,  ##__VA_ARGS__)
#define OTA_ERR(fmt, ...) printk("ota: %s: " fmt, __func__, ##__VA_ARGS__)

#ifdef DEBUG
#define OTA_DBG(fmt, ...) printk("ota: %s (%p): " fmt, __func__, \
				 sys_thread_self_get(), ##__VA_ARGS__)
#else
#define OTA_DBG(...)
#endif