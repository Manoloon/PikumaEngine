                    PRIMERA CONFIGURACIÓN
                           │
                           ▼
                 ┌──────────────────┐
                 │ FetchContent     │
                 │ SFML / ImGui /   │
                 │ ImGui-SFML       │
                 └────────┬─────────┘
                          │
                          ▼
                  Compilar externals
                          │
                          ▼
                 third_party/install/
                          │
              ┌───────────┴───────────┐
              ▼                       ▼
       borrar build/             conservar
              │                 third_party/
              ▼                       │
        recompilar SOLO               │
        tu proyecto ◄─────────────────┘