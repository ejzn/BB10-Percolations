/*
 * Copyright 2012 Research In Motion Limited.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <bps/bps.h>
#include <pthread.h>
#include <json/reader.h>
#include <screen/screen.h>
#include <sys/types.h>
#include <sys/platform.h>
#include <sstream>
#include <string>
#include "screen_js.hpp"


Screen::Screen(const std::string& id) : m_id(id)
{
}

char* onGetObjList()
{
    // Return list of classes in the object
    static char name[] = "Screen";
    return name;
}

JSExt* onCreateObject(const std::string& className, const std::string& id)
{
    // Make sure we are creating the right class
    if (className != "Screen") {
        return 0;
    }

    return new Screen(id);
}

string Screen::InvokeMethod(const string& command)
{
    if (command == "keepAlive") {
        if (preventSleep()) {
            return "Awesome it worked";
        }
        return "We could not properly set the KEEP_ALIVE on the screen";

    } else {
        return "InvokeMethod unsupported command: '" + command + "'";
    }
}

bool Screen::CanDelete()
{
    return true;
}

bool Screen::preventSleep() {
    int idle_mode, rc;
    screen_context_t screen_ctx;
    screen_window_t screen_win;

    /*
     * Create the screen context so we can get access to lib screen events
     */
    rc = screen_create_context(&screen_ctx, 0);
    if (rc) {
        perror("screen_create_context");
        return false;
    }

    /*
     * Get a handle on the window
     */
    rc = screen_create_window(&screen_win, screen_ctx);
    if (rc) {
        perror("screen_create_window");
        return false;
    }

    /*
     * Set the screen as always on
     */
    idle_mode = SCREEN_IDLE_MODE_KEEP_AWAKE;
    rc = screen_set_window_property_iv(screen_win, SCREEN_PROPERTY_IDLE_MODE, &idle_mode);

    if (rc) {
        perror("screen_get_window_property_iv");
        return false;
    }

    return true;
}
