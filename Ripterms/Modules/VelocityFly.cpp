#include "Modules.h"

void Ripterms::Modules::VelocityFly::renderGUI()
{
	ImGui::Checkbox("VelocityFly", &enabled);
	if (enabled)
	{
		ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 15.0f);
		ImGui::BeginGroup();
		ImGui::SliderFloat("Speed", &speed, 0.01f, 2.0f, "%.2f");
		ImGui::EndGroup();
	}
}

void Ripterms::Modules::VelocityFly::onUpdateWalkingPlayer(JNIEnv* env, EntityPlayerSP& this_player, bool* cancel)
{
	if (!enabled) return;
	Ripterms::Maths::Vector3d motion = this_player.getMotion();

	if (GetKeyState(0x5A) & 0x8000)
	{
		Ripterms::Maths::Vector3d additional = Ripterms::Maths::getCameraVector(this_player.getRotation(), speed);
		motion.x += additional.x;
		motion.z += additional.z;
	}
	else if (GetKeyState(0x51) & 0x8000)
	{
		float x = this_player.getRotation().x - 90;
		float y = this_player.getRotation().y;
		Ripterms::Maths::Vector2d rotation = { x, y };
		Ripterms::Maths::Vector3d additional = Ripterms::Maths::getCameraVector(rotation, speed);
		motion.x += additional.x;
		motion.z += additional.z;
	}
	else if (GetKeyState(0x44) & 0x8000)
	{
		float x = this_player.getRotation().x + 90;
		float y = this_player.getRotation().y;
		Ripterms::Maths::Vector2d rotation = { x, y };
		Ripterms::Maths::Vector3d additional = Ripterms::Maths::getCameraVector(rotation, speed);
		motion.x += additional.x;
		motion.z += additional.z;
	}
	else if (GetKeyState(0x53) & 0x8000)
	{
		float x = this_player.getRotation().x + 180;
		float y = this_player.getRotation().y;
		Ripterms::Maths::Vector2d rotation = { x, y };
		Ripterms::Maths::Vector3d additional = Ripterms::Maths::getCameraVector(rotation, speed);
		motion.x += additional.x;
		motion.z += additional.z;
	}
	if (GetKeyState(VK_SPACE) & 0x8000)
		motion.y = speed + 0.75;
	else if (GetKeyState(VK_LSHIFT) & 0x8000)
		motion.y = -speed - 0.75;
	else motion.y = 0.0;

	if (!this_player.isOnGround())
		this_player.setMotion(motion);
}