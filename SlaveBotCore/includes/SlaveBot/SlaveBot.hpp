#pragma once

#include "tlib/Timer.hpp"
#include <dpp/dpp.h>

#define DEBUG_TIMER
#define DEBUG_COMMANDS

//slave bot
namespace sb
{
	class SlaveBot : public dpp::cluster
	{
	public:
		const std::string PREFIX = std::string("!");
	private:
//#define APX std::string("!")+

#define COMMANDS(...) static const std::vector<std::string> CommandsList()\
{\
	const std::vector<std::string> COMMANDS_LIST = {##__VA_ARGS__};\
    return COMMANDS_LIST;\
}

//#define COMMAND(command) std::string(PREFIX + std::string(##command)).c_str()


		using sec_t = tlib::uoft::second_t;
		using min_t = tlib::uoft::minute_t;
		using ho_t = tlib::uoft::hour_t;

		using s_t = tlib::uoft::Second;
		using m_t = tlib::uoft::Minute;
		using h_t = tlib::uoft::Hour;

		using timer_t = tlib::timer<s_t>;
	public:

		SlaveBot(const std::string& token, uint32_t intents = dpp::i_default_intents,
						uint32_t shards = 0, uint32_t cluster_id = 0, uint32_t maxclusters = 1,
						bool compressed = true, dpp::cache_policy_t policy = { dpp::cp_aggressive,
						dpp::cp_aggressive, dpp::cp_aggressive }, uint32_t request_threads = 12,
						uint32_t request_threads_raw = 1) : dpp::cluster(token, intents, shards, cluster_id,
																		 maxclusters, compressed, policy,
																		 request_threads, request_threads_raw) {}

		/*
		* Sets role to user who will push on the reaction
		* @param const dpp::message& msg, const std::string& reaction, const dpp::snowflake& role
		*/
		//void SetRoleByReac(const dpp::message& msg, const std::string& reaction, const dpp::snowflake& role) const;

		void MakeTimer(const dpp::message_create_t& e);

		void StopTimer(const dpp::message_create_t& e);

		COMMANDS("!timer ", "!Fhelp"/*, "!stopTimer"*/)
		
		/*
		* prints all commands of bot
		*/
		void PrintAllCommands(const dpp::message_create_t& e) noexcept;

		/*
		* prints received command to console
		*/
		//void DebugReceivedCommand(const std::string& command) const noexcept;

	private:
		bool isTimer = false;//does timer works

		timer_t timer;
	};
}
