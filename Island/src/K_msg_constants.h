#include <string>


//Item action msgs

//exit msgs
const std::string emsg_north		= "You go north";
const std::string emsg_south		= "You go south";
const std::string emsg_east			= "You go east";
const std::string emsg_west			= "You go west";

const std::string emsg_fail			= "It is locked.";

//actions msgs
const std::string amsg_swear		= "That kind of talk isn't allowed in this adventure simulation.";

//fail msgs
const std::string fmsg_go			= "You cannot go there.";
const std::string fmsg_godir		= "You cannot go that way.";
const std::string fmsg_look			= "You cannot see that here.";
const std::string fmsg_take			= "You cannot see that here.";
const std::string fmsg_takeOwned	= "You already have that!";
const std::string fmsg_drop			= "You do not have that.";
const std::string fmsg_kill			= "You cannot kill something which you cannot see!";
const std::string fmsg_kill_with	= "You cannot kill with that!";
const std::string fmsg_kill_item	= "You are unable to kill it.";
const std::string fmsg_hit			= "You cannot see that to hit it!";
const std::string fmsg_throw		= "You cannot throw that!";

//console msgs
const std::string cmsg_command		= "What do you do? ";
const std::string cmsg_name			= "Please enter your name to start, or 'quit' to quit\n\n>";
const std::string cmsg_quit			= "Are you sure you want to quit? >";
const std::string cmsg_general_question = "Are you sure you wish to do that? >";

//console fail msgs
const std::string cfmsg_noCommand	= "That is not a valid command.";

//display msgs
const std::string dmsg_inroom		= "Here you can see:";
const std::string dmsg_inventory	= "Your current inventory:";
const std::string dmsg_dead			= "You have died!";

//lose msgs
const std::string lmsg_mindpowers	= "You begin to think harder and harder. Suddenly, your brain doubles in size and  explodes outward from your skull.";

//green msgs
const std::string gmsg_dirn			= "An exit to the north has been discovered!";
const std::string gmsg_dirs			= "An exit to the south has been discovered!";
const std::string gmsg_dire			= "An exit to the east has been discovered!";
const std::string gmsg_dirw			= "An exit to the west has been discovered!";