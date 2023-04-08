#include "../includes/SlaveBot/SlaveBot.hpp"

#include "../includes/SlaveBot/utils/Log.hpp"

#include <iomanip>

namespace sb
{
    void SlaveBot::MakeTimer(const dpp::message_create_t& e)
    {
#ifdef DEBUG_COMMANDS
        LOG_INFO(e.msg.content);
#endif // DEBUG_COMMANDS

        const std::string request(e.msg.content);
        
        s_t _time{ 0 };
        const Utils::byte_t charsToTime = CommandsList()[0].size();
        Utils::byte_t charsToTimeType = charsToTime;//to time_t type(Second, minute_t, hour_t)
        std::string time_t;//time_t from str

#pragma region find count of chars to time type
        for (Utils::byte_t i = 0; request[i + charsToTime] != ' '; i++)
        {
            time_t.push_back(request[i + charsToTime]);//add numbers from str
            charsToTimeType++;
        }
#pragma endregion
        if (charsToTimeType != charsToTime && time_t.size() != 0)
        {
            std::string typeOfTime;
            std::string _timeType(request.substr(charsToTimeType, request.size()));
            for (Utils::byte_t i = 1; i < _timeType.size() + 1; i++)
            {
                if (request[i + charsToTimeType] == ' ') break;
                typeOfTime.push_back(request[i + charsToTimeType]);
            }
            if (typeOfTime.size() != 1)
            {
                typeOfTime.pop_back();
            }
            if (typeOfTime == m_t::get_name())
            {
                _time.time_in_seconds = atof(time_t.c_str()) * pow(tlib::uoft::TIME_BASE, m_t::to_divide_seconds());
            }
            else if (typeOfTime == h_t::get_name())
            {
                _time.time_in_seconds = atof(time_t.c_str()) * pow(tlib::uoft::TIME_BASE, h_t::to_divide_seconds());
            }
            else if (typeOfTime == s_t::get_name())
            {
                _time.time_in_seconds = atoi(time_t.c_str()) * pow(tlib::uoft::TIME_BASE, s_t::to_divide_seconds());
            }
            if (_time.time_in_seconds >= 1) _time.time_in_seconds--;
            if (_time > s_t(24))
            {
                dpp::message error_big_time = dpp::message(e.msg.channel_id, "error: available time cannot be bigger than 24 hours or 1'440 minutes, or 86'400 seconds",
                                                               dpp::message_type::mt_reply).set_reference
                                                               (e.msg.id, e.msg.guild_id,
                                                                e.msg.channel_id);
                message_create(error_big_time);
            }
            else if (_time == s_t(0))
            {
                dpp::message error_zero_time = dpp::message(e.msg.channel_id, "error: available time cannot be bigger than 24 hours or 1'440 minutes, or 86'400 seconds",
                    dpp::message_type::mt_reply).set_reference
                    (e.msg.id, e.msg.guild_id,
                        e.msg.channel_id);
                message_create(error_zero_time);
            }
            //timer starts
            else
            {
#ifdef DEBUG_TIMER
                LOG_INFO("(TIMER)TIME IN SECONDS: " << _time.time_in_seconds);
#endif // DEBUG
                //timer_t timer(_time);
                timer.set_new_time(_time);
                isTimer = true;
                std::thread start([this] {timer.start();});
                std::thread timer_work([&]
                                       {
                                           const dpp::message _start = dpp::message(e.msg.channel_id, "timer has just started the work!",
                                           dpp::message_type::mt_reply).set_reference
                                           (e.msg.id, e.msg.guild_id,
                                            e.msg.channel_id);
                
                message_create(_start);
                unsigned int time_to_end = atof(time_t.c_str()) / 4;
                while (true)
                {
                    if (timer.is_stopped() || !isTimer)
                    {
#ifdef DEBUG_TIMER
                        LOG_INFO("(TIMER)TIMER HAS JUST ENDED THE WORK! | ELAPSED TIME: " << timer.elapsed_time());
#endif // DEBUG
                        //print end!
                        const dpp::message _end = dpp::message(e.msg.channel_id, "timer has just ended the work!",
                                                               dpp::message_type::mt_reply).set_reference
                                                               (e.msg.id, e.msg.guild_id,
                                                                e.msg.channel_id);
                        isTimer = false;
                        message_create(_end);
                        break;
                    }
                    else if (!timer.is_stopped() && timer.is_updated())
                    {
                        
                        if (timer.elapsed_time().time_in_seconds == time_to_end/* && timer.get_start_time().time_in_seconds != atof(time_t.c_str())*/)
                        {
#ifdef DEBUG_TIMER
                            LOG_INFO("(TIMER)ELAPSED TIME: " << timer.elapsed_time() << " | TIME TO END : " << timer.time_to_end());
#endif // DEBUG 
                            const std::string to_send("time to end is: " + std::to_string(time_to_end) + " second " + " of started " + std::to_string(_time.time_in_seconds + 1) + " seconds");
                            const dpp::message how_time_elapsed = dpp::message(e.msg.channel_id, to_send,
                                                                               dpp::message_type::mt_reply).set_reference
                                                                               (e.msg.id, e.msg.guild_id,
                                                                                e.msg.channel_id);
                            message_create(how_time_elapsed);
                            time_to_end *= 2;
                        }
                    }
                }
                                       });
                start.join();
                timer_work.join();
            }
        }
        timer.clear();
    }

    void SlaveBot::StopTimer(const dpp::message_create_t& e)
    {
        if (isTimer)
        {
            isTimer = false;
            timer.start(false);
            timer.clear();
        }
        else
        {
            dpp::message timer_is_not_working = dpp::message(e.msg.channel_id, "timer is not running", dpp::mt_reply)
                .set_reference(e.msg.id, e.msg.guild_id, e.msg.channel_id);
            message_create(timer_is_not_working);
        }
    }

    void SlaveBot::PrintAllCommands(const dpp::message_create_t& e) noexcept
    {
#ifdef DEBUG_COMMANDS
        LOG_INFO(e.msg.content);
#endif // DEBUG_COMMANDS

        std::string commands;
        commands += std::string("All available commands are:\n");
        for (Utils::byte_t i = 0; i < CommandsList().size(); i++)
        {
            commands += CommandsList()[i] + '\n';
        }
        const dpp::message help_command = dpp::message(e.msg.channel_id, commands,
                                                       dpp::message_type::mt_reply).set_reference
                                                       (e.msg.id, e.msg.guild_id,
                                                        e.msg.channel_id);

        message_create(help_command);
    }
}
