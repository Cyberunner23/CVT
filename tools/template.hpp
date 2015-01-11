/*
Copyright 2014 Alex Frappier Lachapelle

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

#ifndef CMLOGGERVER_HPP
#define CMLOGGERVER_HPP

#ifdef USE_IN_SOUL_ENGINE
namespace SE::IO{
#endif

class CMLoggerVer{

public:

    struct CMLoggerVerStruct{
        int major;
        int minor;
        int patch;
        int build;
    };

    CMLoggerVer(){

        CMLoggerLibVer.major = <VER_MAJOR>;
        CMLoggerLibVer.minor = <VER_MINOR>;
        CMLoggerLibVer.patch = <VER_PATCH>;
        CMLoggerLibVer.build = <VER_BUILD>;

    }

    CMLoggerVerStruct getCMLoggerVer(){
        return CMLoggerLibVer;
    }

private:

    CMLoggerVerStruct CMLoggerLibVer;

};

#ifdef USE_IN_SOUL_ENGINE
}
#endif

#endif // CMLOGGERVER_HPP
