add_library(DandanLib)

target_sources(
    DandanLib PRIVATE Card.cpp
                        ManaAbility.cpp
                        WithDamage.cpp
                        ReplacementAbility.cpp
                        EntersBattlefieldEvent.cpp
                        EntersTappedEffect.cpp
                        PeekEffect.cpp
                        ScryEffect.cpp
                        TriggeredAbility.cpp
)

target_link_libraries(DandanLib PRIVATE nlohmann_json::nlohmann_json)