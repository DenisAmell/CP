#ifndef WORK_CALENDAR_H
#define WORK_CALENDAR_H

#include <iostream>
#include <string>

struct key
{
    size_t _id;
};

enum class type_of_meeting
{
    DAILY,
    BASED_ON_RESULTS_OF_REPORTING_PERIOD,
    INTERVIEW,
    CORPORATE
};

enum class format
{
    FACE_TO_FACE,
    REMOTE
};

struct value
{
    type_of_meeting _type_of_meeting;
    format _format;

    std::string _meeting_description;
    std::string _link_to_meeting;
    std::string _first_name;
    std::string _last_name;
    std::string _middle_name;
    std::string _data;
    std::string _time;
    std::string _duration_of_meeting;
    std::string _list_invitees;
};

#endif // WORK_CALENDAR_H