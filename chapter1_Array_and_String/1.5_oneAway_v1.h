#include <string>
class oneAwayProblem{
	public:
		bool oneAway(std::string one, std::string two);
		bool oneEditAway(std::string one, std::string two, int edits);
		bool oneReplacementAway(std::string one, std::string two, int edits);
};