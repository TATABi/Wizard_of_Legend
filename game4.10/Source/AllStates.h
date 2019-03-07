#include <vector>

namespace game_framework {
	class AllStates : public CGameState
	{
	public:
		AllStates();
		void MoveTo(int);	// ���ʨ��LStates
		int NowState();
	private:
		int _level;
		std::vector<CGameStateRun *> _states;
	};

}