#pragma once

#include "Platform.h"

// eventually, these should be pushed onto stacks maintained by Context
void enableWireframe();
void disableWireframe();
GLint getNumExtensions();
bool extensionSupported(const std::string &aExtName);