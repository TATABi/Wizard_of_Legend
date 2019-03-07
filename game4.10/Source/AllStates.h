#include <vector>

namespace game_framework {
	class AllStates : public CGameState
	{
	public:
		AllStates();
		void MoveTo(int);	// 移動到其他States
		int NowState();
	private:
		int _level;
		std::vector<CGameStateRun *> _states;
	};

}