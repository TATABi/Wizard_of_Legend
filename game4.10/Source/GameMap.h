namespace game_framework {

	class GameMap {
	public:
		GameMap(int, int);  // �]�w��l�����I
		~GameMap();
		void Initialize(int, int);
		void LoadBitmap();
		void OnMove();
		void OnShow();
		void SetCharacterXY(int, int);

	private:
		int _map[160][160] = { 0 };
		int _cx, _cy;  //����ҦbMap���y��
		CMovingBitmap _background; //�I����
		CMovingBitmap _wall;	//�ΨӼ���3D�e��
		int cm[4];   //(x,y,l,w) collision_move
		int collision_damage[4];
	};

}