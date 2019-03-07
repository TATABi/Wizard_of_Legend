namespace game_framework {
	class Character {
	public:
		Character();
		void Initialize();
		void OnMove();					// �������l
		void OnShow();					// �N���l�ϧζK��e��
		void SetMovingDown(bool flag);	// �]�w�O�_���b���U����
		void SetMovingLeft(bool flag);	// �]�w�O�_���b��������
		void SetMovingRight(bool flag); // �]�w�O�_���b���k����
		void SetMovingUp(bool flag);	// �]�w�O�_���b���W����
		void SetXY(int x, int y);		// �]�w���l���W���y��
		
	private:
		int _x, _y;
		CMovingBitmap _pic;
		int _hp;
		int _mp;
		
	};
}