#pragma once

#include "stdafx.h"

void wait_for_a_write(uv_idle_t* handle);
void wait_async(uv_async_t* handle);