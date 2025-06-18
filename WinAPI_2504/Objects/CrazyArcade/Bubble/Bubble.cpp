#include "Framework.h"

Bubble::Bubble()
{
	bubble = new RectCollider({ TILE_SIZE }); // 이거 생성할때, 충돌처리했던것처럼 그 위치범위에있으면 해당 타일 pos받아오자
	//물풍선 터트릴때, 물줄기 방향따라 sprite니까 값주고, 위치 값 넣은 배열을 아예 넘겨버리자! 근데 이것도 계속 등록해제등록해제 이렇게될텐데, 괜찮나?
	//오 여러개 생성하면 등록해제가 좀 복잡해지겠네 고민좀 하자 음 인스턴싱은 계속 위치가 바뀌니까 알맞지않은 것 같다.

}

Bubble::~Bubble()
{
}
