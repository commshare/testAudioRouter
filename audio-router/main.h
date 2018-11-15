#pragma once

#include "..\audio-router-gui\routing_params.h"
#include "..\audio-router-gui\wtl.h"

//需要gui的参数
bool apply_parameters(const local_routing_params&);
//应用路由
bool apply_implicit_routing();