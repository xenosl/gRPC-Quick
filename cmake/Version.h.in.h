#pragma once

#define SHUHAI_GRPC_VERSION_MAJOR @PROJECT_VERSION_MAJOR@
#define SHUHAI_GRPC_VERSION_MINOR @PROJECT_VERSION_MINOR@
#define SHUHAI_GRPC_VERSION_PATCH @PROJECT_VERSION_PATCH@

#define SHUHAI_GRPC_VERSION_NUMBER \
    (SHUHAI_GRPC_VERSION_MAJOR * 10000 + SHUHAI_GRPC_VERSION_MINOR * 100 + SHUHAI_GRPC_VERSION_PATCH)

#define SHUHAI_GRPC_VERSION "@PROJECT_VERSION@"