#include <chrono>
#include <iostream>

int main()
{
   using namespace std::chrono_literals;
   
   auto d1 = 1h + 20min + 30s ;
   auto d2 = 17h + 40min + 20s;
   if(d2 > d1)
     std::cout << "d2 > d1 " << std::endl;

   //Chrono various Options
   std::chrono::hours hr(12h);
   std::chrono::minutes mts(30min);
   std::chrono::seconds sec(50s);
   std::chrono::milliseconds  ms(100ms);
   std::chrono::microseconds mic_s(100us);
   std::chrono::nanoseconds ns(100ns);

   //conversion functions
   std::chrono::hours hr1(20);
   std::chrono::minutes mts1(hr1);  

   auto  seconds =  std::chrono::duration_cast<std::chrono::seconds>(60min);
   auto  minutes =  std::chrono::duration_cast<std::chrono::minutes>(1h);
   auto  hours   =  std::chrono::duration_cast<std::chrono::hours>(60min);

   auto  h       =  std::chrono::ceil<std::chrono::minutes>(60min);
   auto  l       =  std::chrono::floor<std::chrono::seconds>(60min);
   auto  a       =  std::chrono::abs(60min);
   auto  r       =  std::chrono::round<std::chrono::minutes>(60min);

   std::cout << " Current Time = " << std::chrono::system_clock::now() << std::endl ;


   /*  C++-20 Feature - Support Calendar
    *  Supports UTC, Atomic Time Clock, GPS Clock
    */
   std::chrono::year_month_day d = 1982y/9/2d;
   std::chrono::year_month_weekday d3 =  std::chrono::January/std::chrono::Monday[1]/2025;
   std::chrono::sys_days sdate = 2024y/std::chrono::September/02d;
   std::cout << "sdate  = " << sdate << std::endl;
   std::cout << "Weekday = " << d3 << std::endl ;

   /* it gives time point*/
   auto today = std::chrono::floor<std::chrono::days>(std::chrono::system_clock::now());
   std::cout << "today = " << today << std::endl;

   /*convert time point to calendar*/
   std::chrono::year_month_day today_date {today};
    

   std::chrono::year_month_day first_day_month  =  today_date.year()/ today_date.month() /1;
   std::chrono::year_month_day last_day_month  =  today_date.year()/ today_date.month() / std::chrono::last;
   std::cout << "first_day_month = " << first_day_month << std::endl;
   std::cout << "last_day_month = " << last_day_month << std::endl;

   /*check date is valid */
   std::cout << first_day_month.ok() << std::endl;
   
   //convert time to hh::mm::ss
   std::chrono::hh_mm_ss<std::chrono::seconds> time_to(12h + 15min +11s);
   std::cout << "time_to " << time_to << std::endl;
  
   //represent time in different zone by defaults time is in UTC
   auto tz = std::chrono::zoned_time{std::chrono::current_zone(), std::chrono::system_clock::now()};
   auto tz_europe  = std::chrono::zoned_time{std::chrono::locate_zone("Eurrope/Rome"), std::chrono::system_clock::now()};
  //represent a time point in a specific time zone
  auto t = std::chrono::local_days {2024y/std::chrono::June/1} + 12h + 15min + 12s + 256ms;
  auto ny_time = std::chrono::zoned_time(std::chrono::locate_zone("America/New York"), t);
  //convert time from one timezone to into another
  auto converted_time = std::chrono::zoned_time<std::chrono::milliseconds>(std::chrono::locate_zone("America/Los Angeles"), ny_time);

}
