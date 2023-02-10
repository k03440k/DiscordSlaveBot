//#include "fuckingSlave/tlib/timer/timer.h"
#include <SlaveBot/SlaveBot.hpp>
//#include <map>
using namespace sb;
/* Be sure to place your token in the line below.
 * Follow steps here to get a token:
 * https://dpp.dev/creating-a-bot-application.html
 * When you invite the bot, be sure to invite it with the
 * scopes 'bot' and 'applications.commands', e.g.
 * https://discord.com/oauth2/authorize?client_id=940762342495518720&scope=bot+applications.commands&permissions=139586816064
 */

int main()
{
    std::string BOT_TOKEN = "MTAzMTIzNTcwOTQ2MzQyOTE2MQ.G6QuV_.UCcd5NQCAaALFw4XeeEzJPKkGvzf2HMaBZ-NRE";
    SlaveBot bot(BOT_TOKEN, dpp::i_default_intents | dpp::i_message_content);
    bot.on_log(dpp::utility::cout_logger());
    bot.on_message_create([&bot](const dpp::message_create_t& event)
                          {
                              //content of event
                              const std::string CT = event.msg.content;
    if (event.msg.author != bot.me)
    {
        std::cout << "\nCALLED\n";
        if (CT.find(bot.CommandsList()[0]) != std::string::npos)
        {
            bot.MakeTimer(event);
        }
        else if (CT.find(bot.CommandsList()[2]) != std::string::npos)
        {
            bot.StopTimer(event);
        }
        else if (CT.find(bot.CommandsList()[1]) != std::string::npos)
        {
            bot.PrintAllCommands(event);
        }
    }
    /*dpp::collected_reaction a1;
    a1.react_guild->id = event.msg.guild_id;
    std::cout << a1.react_user.username;*/
    });

    bot.start(dpp::st_wait);

    return 0;
}