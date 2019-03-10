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
		int _map[1600][1600];
		int _cx, _cy;  //����Ҧb�y��
		CMovingBitmap _background; //�I����
		CMovingBitmap _wall;	//�ΨӼ���3D�e��
		CMovingBitmap _terrain; //�a��²��
	};

}