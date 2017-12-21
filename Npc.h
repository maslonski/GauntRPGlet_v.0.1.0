#include "Humans.h"


class Npc : public Humans
{
	public:
		Npc(const Sprite &, float2, float);
		virtual ~Npc();

		void draw();
		void update();

		bool getOstDialog() { return ostDialog; }

	protected:
	     bool ostDialog:1;
	private:

};
