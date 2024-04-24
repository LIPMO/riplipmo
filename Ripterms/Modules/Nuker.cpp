#include "Modules.h"
#include "../Cache/Cache.h"
#include <ImGui/imgui.h>
#include "../../net/minecraft/network/play/client/C07PacketPlayerDigging/C07PacketPlayerDigging.h"

void Ripterms::Modules::Nuker::run()
{
	if (!enabled) return;
	Ripterms::Maths::Vector3d player_pos{ Ripterms::cache->thePlayer.getPosition() };

	static std::chrono::steady_clock::time_point last_run = std::chrono::steady_clock::now();

	std::chrono::steady_clock::time_point current_time = std::chrono::steady_clock::now();
	std::chrono::duration<double> elapsed_seconds = current_time - last_run;

	if (elapsed_seconds.count() >= delay)
	{
		// NUKING!!!
		for (int i = -blocksx; i <= blocksxx; ++i) {
			for (int j = -blocksy; j <= blocksyy; ++j) {
				for (int k = -blocksz; k <= blockszz; ++k) {
					Ripterms::Maths::Vector3d block_pos{ player_pos.x + i, player_pos.y + j, player_pos.z + k };

					int x = static_cast<int>(std::floor(block_pos.x));
					int y = static_cast<int>(std::floor(block_pos.y));
					int z = static_cast<int>(std::floor(block_pos.z));

					Ripterms::cache->thePlayer.getSendQueue().addToSendQueue(C07PacketPlayerDigging::new_object(0, (int)std::floor(block_pos.x), (int)std::floor(block_pos.y), (int)std::floor(block_pos.z), 0));
					Ripterms::cache->thePlayer.getSendQueue().addToSendQueue(C07PacketPlayerDigging::new_object(2, (int)std::floor(block_pos.x), (int)std::floor(block_pos.y), (int)std::floor(block_pos.z), 0));

				}
			}
		}
		last_run = current_time;
	}
}

void Ripterms::Modules::Nuker::renderGUI()
{
	ImGui::Checkbox("Nuker", &enabled);
	ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 15.0f);
	ImGui::BeginGroup();
	ImGui::SliderFloat("-X", &blocksx, 0.0f, 5.0f, "%.1f");
	ImGui::SliderFloat("X", &blocksxx, 0.0f, 5.0f, "%.1f");
	ImGui::SliderFloat("-Y", &blocksy, 0.0f, 5.0f, "%.1f");
	ImGui::SliderFloat("Y", &blocksyy, 0.0f, 5.0f, "%.1f");
	ImGui::SliderFloat("-Z", &blocksz, 0.0f, 5.0f, "%.1f");
	ImGui::SliderFloat("Z", &blockszz, 0.0f, 5.0f, "%.1f");
	ImGui::SliderFloat("Delay", &delay, 0, 20);
	ImGui::EndGroup();
}
