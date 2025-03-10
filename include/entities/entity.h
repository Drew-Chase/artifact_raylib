#pragma once

namespace artifact {
class Entity {
protected:
		// Statistics
        int max_health = 5;
        int health = max_health;
        int attack_damage = 1;
		bool is_on_ground = true;


		// Multipliers
        float walk_speed_multiplier = 1.f;
};
} // artifact
