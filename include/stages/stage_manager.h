#pragma once
#include <concepts>
#include <type_traits>


#include "stage.h"
#include "title_screen.h"

namespace artifact
{
    static auto TITLE_SCREEN = new TitleScreen();

    class StageManager
    {

        Stage *current_stage = nullptr;

    public:
        StageManager();
        ~StageManager();

        template<class T>
            requires std::is_base_of_v<Stage, std::remove_pointer_t<T>>
        Stage *load_stage(T stage)
        {
            // destroy the current stage
            if (current_stage != nullptr)
                current_stage->destroy();

            current_stage = stage;
            current_stage->startup();
            current_stage->update(true);
            current_stage->draw(true);
            return stage;
        }


        [[nodiscard]] Stage *getCurrentStage() const { return current_stage; }
    };
} // namespace artifact
