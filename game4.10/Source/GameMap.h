namespace game_framework {

	class GameMap
	{
	public:
		GameMap();
		int  GetX1();					// ���l���W�� x �y��
		int  GetY1();					// ���l���W�� y �y��
		void Initialize();				// �]�w���l����l��
		void OnShow();					// �N���l�ϧζK��e��
		void SetXY(int x, int y);		// �]�w���l���W���y��
		void RandomMap();
	private:
		int _x, _y;					// ���l���W���y��
		CMovingBitmap _pic;
	};
}