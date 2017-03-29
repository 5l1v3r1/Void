#include "VTime.h"
#include "../../Utility/Logger/VLogger.h"
#include <sstream>
#include <iomanip>

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VTime
    //----------------------------------------------------------------------------------------------------
    VTime VTime::Now()
    {
         std::chrono::time_point<std::chrono::system_clock, std::chrono::milliseconds> timePoint = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now());
        std::time_t timestamp = timePoint.time_since_epoch().count();
        return VTime(timestamp);
    }
    
    //----------------------------------------------------------------------------------------------------
    VTime::VTime()
        :
        mTime(0)
    {
    }
    
    //----------------------------------------------------------------------------------------------------
    VTime::VTime(std::time_t _time)
        :
        mTime(_time)
    {
        
    }
    
    //----------------------------------------------------------------------------------------------------
    VTime::VTime(const VTime& _time)
        :
        mTime(_time.mTime)
    {
    }
    
    //----------------------------------------------------------------------------------------------------
    VTime::~VTime()
    {
    }
    
    //----------------------------------------------------------------------------------------------------
    VTime VTime::operator+(const VTime& _time) const
    {
        return VTime(mTime + _time.mTime);
    }
    
    //----------------------------------------------------------------------------------------------------
    VTime VTime::operator-(const VTime& _time) const
    {
        return VTime(mTime - _time.mTime);
    }
    
    //----------------------------------------------------------------------------------------------------
    std::time_t VTime::Timestamp()
    {
        return mTime;
    }
    
    //----------------------------------------------------------------------------------------------------
    std::string VTime::String()
    {
        std::chrono::duration<long long, std::milli> duration = std::chrono::milliseconds(mTime);
        auto timePoint = std::chrono::time_point<std::chrono::system_clock, std::chrono::milliseconds>(duration);
        time_t time = std::chrono::system_clock::to_time_t(timePoint);
        std::tm *tm = std::localtime(&time);
        
        std::stringstream sstream;
        sstream << std::setfill('0');
        sstream << tm->tm_year + 1900 << '-' << std::setw(2) << tm->tm_mon + 1 << '-' << std::setw(2) << tm->tm_mday;
        sstream << ' ';
        sstream << std::setw(2) << tm->tm_hour << ':' << std::setw(2) << tm->tm_min << ':' << std::setw(2) << tm->tm_sec;
        return sstream.str();
    }
    
    // Test
    //----------------------------------------------------------------------------------------------------
    void VTimeTest()
    {
        VTime time = VTime::Now();
        VLogger::Info("Time: %ld", time.Timestamp());
        VLogger::Info("Time string: %s", time.String().c_str());
    }
    
}
