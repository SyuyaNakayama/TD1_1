#include "WallManager.h"

void WallManager::Initialize()
{
	goal_ = std::make_unique<Goal>();
	goal_->Initialize();
	SetStage(1);
}

void WallManager::AllDraw(ViewProjection viewProjection)
{
	for (size_t i = 0; i < walls_.size(); i++) { walls_[i].Draw(viewProjection); }
	goal_->Draw(viewProjection);
}

void WallManager::SetStage(UINT32 stage)
{
	walls_.clear();

	switch (stage)
	{
	case 1:
		walls_.resize(4);
		walls_[0].Initialize({ -50.0f,70.0f }, { 20.0f,100.0f });
		walls_[1].Initialize({ 50.0f,70.0f }, { 20.0f,100.0f });
		walls_[2].Initialize({ 0,-50.0f }, { 70.0f,20.0f });
		walls_[3].Initialize({ 0,190.0f }, { 70.0f,20.0f });
		break;
	case 2:
		walls_.resize(5);
		walls_[0].Initialize({ -50.0f,90.0f }, { 20.0f,120.0f });
		walls_[1].Initialize({ 150.0f,90.0f }, { 20.0f,120.0f });
		walls_[2].Initialize({ 50.0f,-50.0f }, { 120.0f,20.0f });
		walls_[3].Initialize({ 50.0f,230.0f }, { 120.0f,20.0f });
		walls_[4].Initialize({ 50.0f,60.0f }, { 20.0f,100.0f });
		break;
	case 3:
		walls_.resize(11);
		walls_[0].Initialize({ -40.0f,100.0f }, { 20.0f,120.0f });
		walls_[1].Initialize({ 240.0f,100.0f }, { 20.0f,120.0f });
		walls_[2].Initialize({ 100.0f,-40.0f }, { 160.0f,20.0f });
		walls_[3].Initialize({ 100.0f,240.0f }, { 160.0f,20.0f });
		walls_[4].Initialize({ 100.0f,100.0f }, { 40.0f,40.0f });
		walls_[5].Initialize({ 0.0f,80.0f }, { 20.0f,20.0f });
		walls_[6].Initialize({ 80.0f,0.0f }, { 20.0f,20.0f });
		walls_[7].Initialize({ 40.0f,160.0f }, { 20.0f,20.0f });
		walls_[8].Initialize({ 160.0f,40.0f }, { 20.0f,20.0f });
		walls_[9].Initialize({ 120.0f,200.0f }, { 20.0f,20.0f });
		walls_[10].Initialize({ 200.0f,120.0f }, { 20.0f,20.0f });
		break;
	case 4:
		walls_.resize(6);
		walls_[0].Initialize({ -40.0f,180.0f }, { 20.0f,200.0f });
		walls_[1].Initialize({ 240.0f,180.0f }, { 20.0f,200.0f });
		walls_[2].Initialize({ 100.0f,-40.0f }, { 160.0f,20.0f });
		walls_[3].Initialize({ 100.0f,400.0f }, { 160.0f,20.0f });
		walls_[4].Initialize({ 120.0f,60.0f }, { 100.0f,80.0f });
		walls_[5].Initialize({ 90.0f,260.0f }, { 90.0f,80.0f });
		break;
	case 5:
		walls_.resize(8);
		walls_[0].Initialize({ -30.0f,-120.0f }, { 10.0f,140.0f });
		walls_[1].Initialize({ 270.0f,-120.0f }, { 10.0f,140.0f });
		walls_[2].Initialize({ 120.0f,30.0f }, { 160.0f,10.0f });
		walls_[3].Initialize({ 120.0f,-270.0f }, { 160.0f,10.0f });
		walls_[4].Initialize({ 100.0f,-40.0f }, { 120.0f,20.0f });
		walls_[5].Initialize({ 190.0f,-80.0f }, { 30.0f,20.0f });
		walls_[6].Initialize({ 200.0f,-180.0f }, { 60.0f,40.0f });
		walls_[7].Initialize({ 70.0f,-160.0f }, { 50.0f,60.0f });
		break;
	case 6:
		walls_.resize(12);
		walls_[0].Initialize({ -140.0f,20.0f }, { 20.0f,120.0f });
		walls_[1].Initialize({ 140.0f,20.0f }, { 20.0f,120.0f });
		walls_[2].Initialize({ 0.0f,-120.0f }, { 160.0f,20.0f });
		walls_[3].Initialize({ 0.0f,160.0f }, { 160.0f,20.0f });
		walls_[4].Initialize({ -100.0f,40.0f }, { 20.0f,20.0f });
		walls_[5].Initialize({ 60.0f,40.0f }, { 20.0f,20.0f });
		walls_[6].Initialize({ 30.0f,40.0f }, { 10.0f,60.0f });
		walls_[7].Initialize({ -30.0f,60.0f }, { 10.0f,80.0f });
		walls_[8].Initialize({ -60.0f,120.0f }, { 20.0f,20.0f });
		walls_[9].Initialize({ 100.0f,120.0f }, { 20.0f,20.0f });
		walls_[10].Initialize({ -20.0f,-40.0f }, { 60.0f,20.0f });
		walls_[11].Initialize({ 100.0f,-60.0f }, { 20.0f,40.0f });
		break;
	case 7:
		walls_.resize(20);
		walls_[0].Initialize({ -30.0f,-200.0f }, { 10.0f,220.0f });
		walls_[1].Initialize({ 430.0f,-200.0f }, { 10.0f,220.0f });
		walls_[2].Initialize({ 200.0f,30.0f }, { 240.0f,10.0f });
		walls_[3].Initialize({ 200.0f,-430.0f }, { 240.0f,10.0f });
		walls_[4].Initialize({ 30.0f,-50.0f }, { 50.0f,30.0f });
		walls_[5].Initialize({ 30.0f,-150.0f }, { 50.0f,30.0f });
		walls_[6].Initialize({ 50.0f,-250.0f }, { 30.0f,30.0f });
		walls_[7].Initialize({ 50.0f,-370.0f }, { 30.0f,50.0f });
		walls_[8].Initialize({ 150.0f,-50.0f }, { 30.0f,30.0f });
		walls_[9].Initialize({ 150.0f,-150.0f }, { 30.0f,30.0f });
		walls_[10].Initialize({ 150.0f,-250.0f }, { 30.0f,30.0f });
		walls_[11].Initialize({ 150.0f,-370.0f }, { 30.0f,50.0f });
		walls_[12].Initialize({ 250.0f,-30.0f }, { 30.0f,50.0f });
		walls_[13].Initialize({ 250.0f,-150.0f }, { 30.0f,30.0f });
		walls_[14].Initialize({ 250.0f,-250.0f }, { 30.0f,30.0f });
		walls_[15].Initialize({ 250.0f,-350.0f }, { 30.0f,30.0f });
		walls_[16].Initialize({ 350.0f,-30.0f }, { 30.0f,50.0f });
		walls_[17].Initialize({ 350.0f,-150.0f }, { 30.0f,30.0f });
		walls_[18].Initialize({ 370.0f,-250.0f }, { 50.0f,30.0f });
		walls_[19].Initialize({ 370.0f,-350.0f }, { 50.0f,30.0f });
		break;
	case 8:
		walls_.resize(26);
		walls_[0].Initialize({ -30.0f,-280.0f }, { 10.0f,300.0f });
		walls_[1].Initialize({ 590.0f,-280.0f }, { 10.0f,300.0f });
		walls_[2].Initialize({ 280.0f,30.0f }, { 320.0f,10.0f });
		walls_[3].Initialize({ 280.0f,-590.0f }, { 320.0f,10.0f });
		walls_[4].Initialize({ 30.0f,-280.0f }, { 10.0f,240.0f });
		walls_[5].Initialize({ 530.0f,-260.0f }, { 10.0f,220.0f });
		walls_[6].Initialize({ 280.0f,-30.0f }, { 260.0f,10.0f });
		walls_[7].Initialize({ 280.0f,-530.0f }, { 260.0f,10.0f });
		walls_[8].Initialize({ 90.0f,-240.0f }, { 10.0f,140.0f });
		walls_[9].Initialize({ 90.0f,-440.0f }, { 10.0f,20.0f });
		walls_[10].Initialize({ 470.0f,-280.0f }, { 10.0f,180.0f });
		walls_[11].Initialize({ 280.0f,-90.0f }, { 200.0f,10.0f });
		walls_[12].Initialize({ 280.0f,-470.0f }, { 200.0f,10.0f });
		walls_[13].Initialize({ 150.0f,-280.0f }, { 10.0f,120.0f });
		walls_[14].Initialize({ 410.0f,-280.0f }, { 10.0f,120.0f });
		walls_[15].Initialize({ 190.0f,-150.0f }, { 50.0f,10.0f });
		walls_[16].Initialize({ 350.0f,-150.0f }, { 70.0f,10.0f });
		walls_[17].Initialize({ 280.0f,-410.0f }, { 140.0f,10.0f });
		walls_[18].Initialize({ 210.0f,-240.0f }, { 10.0f,20.0f });
		walls_[19].Initialize({ 210.0f,-320.0f }, { 10.0f,20.0f });
		walls_[20].Initialize({ 350.0f,-280.0f }, { 10.0f,60.0f });
		walls_[21].Initialize({ 280.0f,-210.0f }, { 80.0f,10.0f });
		walls_[22].Initialize({ 280.0f,-350.0f }, { 80.0f,10.0f });
		walls_[23].Initialize({ 250.0f,-280.0f }, { 10.0f,20.0f });
		walls_[24].Initialize({ 280.0f,-250.0f }, { 40.0f,10.0f });
		walls_[25].Initialize({ 280.0f,-310.0f }, { 40.0f,10.0f });
		break;
	}
	goal_->SetGoal(stage);
}
