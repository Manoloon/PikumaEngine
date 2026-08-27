
-- Night Day maps 
local curent_hour = os.date("*t").hour;
local current_map_assetID
if  curent_hour > 9 and curent_hour < 19 then
    current_map_assetID = "tilemap-texture"
else
    current_map_assetID = "tilemap-night-texture"
end
--

-- Define a table with the start values of the first level
Level = {
    ----------------------------------------------------
    -- Table to define the list of assets
    -- number of assets : 72
    ----------------------------------------------------
    assets = {
        [0] =
        { type = "texture", id = "tilemap-texture",             file = "./assets/tilemaps/jungle.png" },
        { type = "texture", id = "tilemap-night-texture",       file = "./assets/tilemaps/jungle-night.png" },
        { type = "texture", id = "chopper-texture",             file = "./assets/images/chopper-green-spritesheet.png" },
        { type = "texture", id = "su27-texture",                file = "./assets/images/su27-spritesheet.png" },
        { type = "texture", id = "f22-texture",                 file = "./assets/images/f22-spritesheet.png" },
        { type = "texture", id = "fw190-texture",               file = "./assets/images/fw190-spritesheet.png" },
        { type = "texture", id = "upf7-texture",                file = "./assets/images/upf7-spritesheet.png" },
        { type = "texture", id = "bf109-texture",               file = "./assets/images/bf109-spritesheet.png" },
        { type = "texture", id = "bomber-texture",              file = "./assets/images/bomber-spritesheet.png" },
        { type = "texture", id = "carrier-texture",             file = "./assets/images/carrier.png" },
        { type = "texture", id = "boat-texture",                file = "./assets/images/boat.png" },
        { type = "texture", id = "tank-tiger-up-texture",       file = "./assets/images/tank-tiger-up.png" },
        { type = "texture", id = "tank-tiger-right-texture",    file = "./assets/images/tank-tiger-right.png" },
        { type = "texture", id = "tank-tiger-down-texture",     file = "./assets/images/tank-tiger-down.png" },
        { type = "texture", id = "tank-tiger-left-texture",     file = "./assets/images/tank-tiger-left.png" },
        { type = "texture", id = "tank-tiger-killed-texture",   file = "./assets/images/tank-tiger-killed.png" },
        { type = "texture", id = "tank-panther-up-texture",     file = "./assets/images/tank-panther-up.png" },
        { type = "texture", id = "tank-panther-right-texture",  file = "./assets/images/tank-panther-right.png" },
        { type = "texture", id = "tank-panther-down-texture",   file = "./assets/images/tank-panther-down.png" },
        { type = "texture", id = "tank-panther-left-texture",   file = "./assets/images/tank-panther-left.png" },
        { type = "texture", id = "tank-panther-killed-texture", file = "./assets/images/tank-panther-killed.png" },
        { type = "texture", id = "truck-ford-up-texture",       file = "./assets/images/truck-ford-up.png" },
        { type = "texture", id = "truck-ford-right-texture",    file = "./assets/images/truck-ford-right.png" },
        { type = "texture", id = "truck-ford-down-texture",     file = "./assets/images/truck-ford-down.png" },
        { type = "texture", id = "truck-ford-left-texture",     file = "./assets/images/truck-ford-left.png" },
        { type = "texture", id = "truck-ford-killed-texture",   file = "./assets/images/truck-ford-killed.png" },
        { type = "texture", id = "army-walk-up-texture",        file = "./assets/images/army-walk-up.png" },
        { type = "texture", id = "army-walk-right-texture",     file = "./assets/images/army-walk-right.png" },
        { type = "texture", id = "army-walk-down-texture",      file = "./assets/images/army-walk-down.png" },
        { type = "texture", id = "army-walk-left-texture",      file = "./assets/images/army-walk-left.png" },
        { type = "texture", id = "army-walk-killed-texture",    file = "./assets/images/army-walk-killed.png" },
        { type = "texture", id = "army-gun-up-texture",         file = "./assets/images/army-gun-up.png" },
        { type = "texture", id = "army-gun-right-texture",      file = "./assets/images/army-gun-right.png" },
        { type = "texture", id = "army-gun-down-texture",       file = "./assets/images/army-gun-down.png" },
        { type = "texture", id = "army-gun-left-texture",       file = "./assets/images/army-gun-left.png" },
        { type = "texture", id = "army-gun-killed-texture",     file = "./assets/images/army-walk-killed.png" },
        { type = "texture", id = "sam-truck-right-texture",     file = "./assets/images/sam-truck-right.png" },
        { type = "texture", id = "sam-tank-left-texture",       file = "./assets/images/sam-tank-left-spritesheet.png" },
        { type = "texture", id = "sam-tank-right-texture",      file = "./assets/images/sam-tank-right-spritesheet.png" },
        { type = "texture", id = "takeoff-base-texture",        file = "./assets/images/takeoff-base.png" },
        { type = "texture", id = "landing-base-texture",        file = "./assets/images/landing-base.png" },
        { type = "texture", id = "runway-texture",              file = "./assets/images/runway.png" },
        { type = "texture", id = "obstacles1-texture",          file = "./assets/images/obstacles-1.png" },
        { type = "texture", id = "obstacles2-texture",          file = "./assets/images/obstacles-2.png" },
        { type = "texture", id = "obstacles3-texture",          file = "./assets/images/obstacles-3.png" },
        { type = "texture", id = "obstacles4-texture",          file = "./assets/images/obstacles-4.png" },
        { type = "texture", id = "obstacles5-texture",          file = "./assets/images/obstacles-5.png" },
        { type = "texture", id = "obstacles6-texture",          file = "./assets/images/obstacles-6.png" },
        { type = "texture", id = "obstacles7-texture",          file = "./assets/images/obstacles-7.png" },
        { type = "texture", id = "tree1-texture",               file = "./assets/images/tree-1.png" },
        { type = "texture", id = "tree2-texture",               file = "./assets/images/tree-2.png" },
        { type = "texture", id = "tree3-texture",               file = "./assets/images/tree-3.png" },
        { type = "texture", id = "tree4-texture",               file = "./assets/images/tree-4.png" },
        { type = "texture", id = "tree5-texture",               file = "./assets/images/tree-5.png" },
        { type = "texture", id = "tree6-texture",               file = "./assets/images/tree-6.png" },
        { type = "texture", id = "tree7-texture",               file = "./assets/images/tree-7.png" },
        { type = "texture", id = "tree8-texture",               file = "./assets/images/tree-8.png" },
        { type = "texture", id = "tree9-texture",               file = "./assets/images/tree-9.png" },
        { type = "texture", id = "tree10-texture",              file = "./assets/images/tree-10.png" },
        { type = "texture", id = "tree11-texture",              file = "./assets/images/tree-11.png" },
        { type = "texture", id = "tree12-texture",              file = "./assets/images/tree-12.png" },
        { type = "texture", id = "tree13-texture",              file = "./assets/images/tree-13.png" },
        { type = "texture", id = "tree14-texture",              file = "./assets/images/tree-14.png" },
        { type = "texture", id = "tree15-texture",              file = "./assets/images/tree-15.png" },
        { type = "texture", id = "tree16-texture",              file = "./assets/images/tree-16.png" },
        { type = "texture", id = "tree17-texture",              file = "./assets/images/tree-17.png" },
        { type = "texture", id = "tree18-texture",              file = "./assets/images/tree-18.png" },
        { type = "texture", id = "tree19-texture",              file = "./assets/images/tree-19.png" },
        { type = "texture", id = "tree20-texture",              file = "./assets/images/tree-20.png" },
        { type = "texture", id = "bullet-texture",              file = "./assets/images/bullet.png" },
        { type = "texture", id = "radar-texture",               file = "./assets/images/radar-spritesheet.png" },
        { type = "font"   , id = "pico8-font-5",                file = "./assets/fonts/pico8.ttf", font_size = 5 },
        { type = "font"   , id = "pico8-font-10",               file = "./assets/fonts/pico8.ttf", font_size = 10 }
    },

    ----------------------------------------------------
    -- table to define the map config variables
    ----------------------------------------------------
    tilemap = {
        map_file = "./assets/tilemaps/jungle.map",
        texture_asset_id = current_map_assetID,
        num_rows = 20,
        num_cols = 25,
        tile_size = 32,
        scale = 2.0
    },

    ----------------------------------------------------
    -- table to define entities and their components 
    -- Number of entities = 120
    ----------------------------------------------------
    entities = {
        [0] =
        {
            -- Player 1
            tag = "player",
            components = {
                transform = {
                    position = { x = 242, y = 110 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                rigidbody = {
                    velocity = { x = 0.0, y = 0.0 }
                },
                sprite = {
                    texture_asset_id = "chopper-texture",
                    width = 32,
                    height = 32,
                    z_index = 5,
                    fixed = false,
                    src_rect_x = 0,
                    src_rect_y = 0
                },
                animation = {
                    num_frames = 2,
                    speed_rate = 10 -- fps
                },
                boxcollider = {
                    width = 32,
                    height = 25,
                    offset = { x = 0, y = 5 }
                },
                health = {
                    health_percentage = 100
                },
                projectile_emitter = {
                    velocity = { x = 200, y = 200 },
                    repeat_frequency = 1, -- seconds
                    duration = 3, -- seconds
                    hit_percentage_damage = 10,
                    friendly = true
                },
                keyboard_controller = {
                    acceleration = 500,
                    max_speed = 300,
                    damping = 0.95
                },
                camera_follow = {
                    position = { x = 242, y = 110 },
                    view_size = {width = 640, height = 360}
                }
            }
        },
        {
            -- Takeoff base 2
            components = {
                transform = {
                    position = { x = 240, y = 113 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "takeoff-base-texture",
                    width = 32,
                    height = 32,
                    z_index = 1
                }
            }
        },
        {
            -- Landing base 3
            components = {
                transform = {
                    position = { x = 1396, y = 493 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "landing-base-texture",
                    width = 32,
                    height = 32,
                    z_index = 1
                }
            }
        },
        {
            -- Radar UI animation 4
            group = "ui",
            components = {
                transform = {
                    position = { x = 10, y = 10 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "radar-texture",
                    width = 64,
                    height = 64,
                    z_index = 7,
                    fixed = true
                },
                animation = {
                    num_frames = 8,
                    speed_rate = 7 -- fps
                }
            }
        },
        {
            -- Runway 5
            components = {
                transform = {
                    position = { x = 940, y = 65 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 270.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "runway-texture",
                    width = 21,
                    height = 191,
                    z_index = 1
                }
            }
        },
        {
            -- Runway 6
            components = {
                transform = {
                    position = { x = 470, y = 385 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "runway-texture",
                    width = 21,
                    height = 191,
                    z_index = 1
                }
            }
        },
        {
            -- Tank 7
            group = "enemies",
            components = {
                transform = {
                    position = { x = 200, y = 497 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "tank-tiger-right-texture",
                    width = 32,
                    height = 32,
                    z_index = 3
                },
                boxcollider = {
                    width = 25,
                    height = 18,
                    offset = { x = 0, y = 7 }
                },
                health = {
                    health_percentage = 100
                },
                projectile_emitter = {
                    velocity = { x = 100, y = 0 },
                    duration = 2, -- seconds
                    repeat_frequency = 1, -- seconds
                    hit_percentage_damage = 20,
                    friendly = false
                }
            }
        },
        {
            -- Tank 8
            group = "enemies",
            components = {
                transform = {
                    position = { x = 785, y = 170 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "tank-panther-up-texture",
                    width = 32,
                    height = 32,
                    z_index = 3
                },
                boxcollider = {
                    width = 17,
                    height = 18,
                    offset = { x = 7, y = 10 }
                },
                health = {
                    health_percentage = 100
                },
                projectile_emitter = {
                    velocity = { x = 0, y = -100 },
                    duration = 4, -- seconds
                    repeat_frequency = 2, -- seconds
                    hit_percentage_damage = 10,
                    friendly = false
                }
            }
        },
        {
            -- Tank 9
            group = "enemies",
            components = {
                transform = {
                    position = { x = 785, y = 250 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "tank-tiger-down-texture",
                    width = 32,
                    height = 32,
                    z_index = 3
                },
                boxcollider = {
                    width = 20,
                    height = 18,
                    offset = { x = 5, y = 7 }
                },
                health = {
                    health_percentage = 100
                },
                projectile_emitter = {
                    velocity = { x = 0, y = 40 },
                    duration = 3, -- seconds
                    repeat_frequency = 3, -- seconds
                    hit_percentage_damage = 10,
                    friendly = false
                }
            }
        },
        {
            -- Tank 10
            group = "enemies",
            components = {
                transform = {
                    position = { x = 785, y = 350 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "tank-panther-left-texture",
                    width = 32,
                    height = 32,
                    z_index = 3
                },
                boxcollider = {
                    width = 25,
                    height = 18,
                    offset = { x = 5, y = 7 }
                },
                health = {
                    health_percentage = 100
                },
                projectile_emitter = {
                    velocity = { x = -50, y = 0 },
                    duration = 3, -- seconds
                    repeat_frequency = 3, -- seconds
                    hit_percentage_damage = 10,
                    friendly = false
                }
            }
        },
        {
            -- Tank 11
            group = "enemies",
            components = {
                transform = {
                    position = { x = 570, y = 520 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "tank-panther-right-texture",
                    width = 32,
                    height = 32,
                    z_index = 3
                },
                boxcollider = {
                    width = 25,
                    height = 18,
                    offset = { x = 5, y = 7 }
                },
                health = {
                    health_percentage = 100
                },
                projectile_emitter = {
                    velocity = { x = 60, y = 0 },
                    duration = 4, -- seconds
                    repeat_frequency = 4, -- seconds
                    hit_percentage_damage = 10,
                    friendly = false
                }
            }
        },
        {
            -- Tank 12
            group = "enemies",
            components = {
                transform = {
                    position = { x = 570, y = 600 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "tank-panther-left-texture",
                    width = 32,
                    height = 32,
                    z_index = 3
                },
                boxcollider = {
                    width = 25,
                    height = 18,
                    offset = { x = 5, y = 7 }
                },
                health = {
                    health_percentage = 100
                },
                projectile_emitter = {
                    velocity = { x = -60, y = 0 },
                    duration = 4, -- seconds
                    repeat_frequency = 4, -- seconds
                    hit_percentage_damage = 10,
                    friendly = false
                }
            }
        },
        {
            -- Tank 13
            group = "enemies",
            components = {
                transform = {
                    position = { x = 1050, y = 170 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "tank-panther-right-texture",
                    width = 32,
                    height = 32,
                    z_index = 3
                },
                boxcollider = {
                    width = 25,
                    height = 18,
                    offset = { x = 5, y = 7 }
                },
                health = {
                    health_percentage = 100
                },
                projectile_emitter = {
                    velocity = { x = 60, y = 0 },
                    duration = 4, -- seconds
                    repeat_frequency = 4, -- seconds
                    hit_percentage_damage = 10,
                    friendly = false
                }
            }
        },
        {
            -- Tank 14
            group = "enemies",
            components = {
                transform = {
                    position = { x = 1170, y = 116 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "tank-panther-down-texture",
                    width = 32,
                    height = 32,
                    z_index = 3
                },
                boxcollider = {
                    width = 17,
                    height = 18,
                    offset = { x = 8, y = 6 }
                },
                health = {
                    health_percentage = 100
                },
                projectile_emitter = {
                    velocity = { x = 0, y = 40 },
                    duration = 2, -- seconds
                    repeat_frequency = 2, -- seconds
                    hit_percentage_damage = 10,
                    friendly = false
                }
            }
        },
        {
            -- Tank 15
            group = "enemies",
            components = {
                transform = {
                    position = { x = 1380, y = 116 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "tank-panther-down-texture",
                    width = 32,
                    height = 32,
                    z_index = 3
                },
                boxcollider = {
                    width = 17,
                    height = 18,
                    offset = { x = 8, y = 6 }
                },
                health = {
                    health_percentage = 100
                },
                projectile_emitter = {
                    velocity = { x = 0, y = 40 },
                    duration = 2, -- seconds
                    repeat_frequency = 2, -- seconds
                    hit_percentage_damage = 10,
                    friendly = false
                }
            }
        },
        {
            -- Tank 16
            group = "enemies",
            components = {
                transform = {
                    position = { x = 1265, y = 240 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "tank-panther-killed-texture",
                    width = 32,
                    height = 32,
                    z_index = 3
                }
            }
        },
        {
            -- Tank 17
            group = "enemies",
            components = {
                transform = {
                    position = { x = 1265, y = 290 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "tank-panther-left-texture",
                    width = 32,
                    height = 32,
                    z_index = 3
                },
                boxcollider = {
                    width = 20,
                    height = 17,
                    offset = { x = 7, y = 7 }
                },
                health = {
                    health_percentage = 100
                },
                projectile_emitter = {
                    velocity = { x = -400, y = 0 },
                    duration = 2, -- seconds
                    repeat_frequency = 2, -- seconds
                    hit_percentage_damage = 10,
                    friendly = false
                }
            }
        },
        {
            -- Tank 18
            group = "enemies",
            components = {
                transform = {
                    position = { x = 640, y = 800 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "tank-tiger-down-texture",
                    width = 32,
                    height = 32,
                    z_index = 3
                },
                boxcollider = {
                    width = 18,
                    height = 20,
                    offset = { x = 7, y = 7 }
                },
                health = {
                    health_percentage = 100
                },
                projectile_emitter = {
                    velocity = { x = 0, y = 100 },
                    duration = 5, -- seconds
                    repeat_frequency = 5, -- seconds
                    hit_percentage_damage = 10,
                    friendly = false
                }
            }
        },
        {
            -- Tank 19
            group = "enemies",
            components = {
                transform = {
                    position = { x = 790, y = 745 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "tank-tiger-left-texture",
                    width = 32,
                    height = 32,
                    z_index = 3
                },
                boxcollider = {
                    width = 25,
                    height = 18,
                    offset = { x = 7, y = 7 }
                },
                health = {
                    health_percentage = 100
                },
                projectile_emitter = {
                    velocity = { x = -60, y = 0 },
                    duration = 10, -- seconds
                    repeat_frequency = 1, -- seconds
                    hit_percentage_damage = 10,
                    friendly = false
                }
            }
        },
        {
            -- Tank 20
            group = "enemies",
            components = {
                transform = {
                    position = { x = 980, y = 790 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "tank-tiger-right-texture",
                    width = 32,
                    height = 32,
                    z_index = 3
                },
                boxcollider = {
                    width = 25,
                    height = 18,
                    offset = { x = 0, y = 7 }
                },
                health = {
                    health_percentage = 100
                },
                projectile_emitter = {
                    velocity = { x = 60, y = 0 },
                    duration = 2, -- seconds
                    repeat_frequency = 1, -- seconds
                    hit_percentage_damage = 10,
                    friendly = false
                }
            }
        },
        {
            -- Tank 21
            group = "enemies",
            components = {
                transform = {
                    position = { x = 1070, y = 870 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "tank-panther-down-texture",
                    width = 32,
                    height = 32,
                    z_index = 3
                },
                boxcollider = {
                    width = 17,
                    height = 20,
                    offset = { x = 8, y = 4 }
                },
                health = {
                    health_percentage = 100
                },
                projectile_emitter = {
                    velocity = { x = 0, y = 100 },
                    duration = 4, -- seconds
                    repeat_frequency = 2, -- seconds
                    hit_percentage_damage = 10,
                    friendly = false
                }
            }
        },
        {
            -- Tank 22
            group = "enemies",
            components = {
                transform = {
                    position = { x = 1190, y = 790 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "tank-panther-up-texture",
                    width = 32,
                    height = 32,
                    z_index = 3
                },
                boxcollider = {
                    width = 17,
                    height = 20,
                    offset = { x = 7, y = 8 }
                },
                health = {
                    health_percentage = 100
                },
                projectile_emitter = {
                    velocity = { x = 0, y = -200 },
                    duration = 2, -- seconds
                    repeat_frequency = 1, -- seconds
                    hit_percentage_damage = 10,
                    friendly = false
                }
            }
        },
        {
            -- Tank 23
            group = "enemies",
            components = {
                transform = {
                    position = { x = 1210, y = 790 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "tank-panther-up-texture",
                    width = 32,
                    height = 32,
                    z_index = 3
                },
                boxcollider = {
                    width = 17,
                    height = 20,
                    offset = { x = 7, y = 8 }
                },
                health = {
                    health_percentage = 100
                },
                projectile_emitter = {
                    velocity = { x = 0, y = -200 },
                    duration = 2, -- seconds
                    repeat_frequency = 1, -- seconds
                    hit_percentage_damage = 10,
                    friendly = false
                }
            }
        },
        {
            -- Tank 24
            group = "enemies",
            components = {
                transform = {
                    position = { x = 1230, y = 790 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "tank-panther-up-texture",
                    width = 32,
                    height = 32,
                    z_index = 3
                },
                boxcollider = {
                    width = 17,
                    height = 20,
                    offset = { x = 7, y = 8 }
                },
                health = {
                    health_percentage = 100
                },
                projectile_emitter = {
                    velocity = { x = 0, y = -200 },
                    duration = 2, -- seconds
                    repeat_frequency = 1, -- seconds
                    hit_percentage_damage = 10,
                    friendly = false
                }
            }
        },
        {
            -- Tank 25
            group = "enemies",
            components = {
                transform = {
                    position = { x = 1250, y = 790 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "tank-panther-up-texture",
                    width = 32,
                    height = 32,
                    z_index = 3
                },
                boxcollider = {
                    width = 17,
                    height = 20,
                    offset = { x = 7, y = 8 }
                },
                health = {
                    health_percentage = 100
                },
                projectile_emitter = {
                    velocity = { x = 0, y = -200 },
                    duration = 2, -- seconds
                    repeat_frequency = 1, -- seconds
                    hit_percentage_damage = 10,
                    friendly = false
                }
            }
        },
        {
            -- Tank 26
            group = "enemies",
            components = {
                transform = {
                    position = { x = 1000, y = 445 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "tank-panther-up-texture",
                    width = 32,
                    height = 32,
                    z_index = 3
                },
                boxcollider = {
                    width = 17,
                    height = 20,
                    offset = { x = 7, y = 8 }
                },
                health = {
                    health_percentage = 100
                },
                projectile_emitter = {
                    velocity = { x = 0, y = -200 },
                    duration = 2, -- seconds
                    repeat_frequency = 1, -- seconds
                    hit_percentage_damage = 10,
                    friendly = false
                }
            }
        },
        {
            -- Tank 27
            group = "enemies",
            components = {
                transform = {
                    position = { x = 1426, y = 760 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "tank-panther-right-texture",
                    width = 32,
                    height = 32,
                    z_index = 3
                },
                boxcollider = {
                    width = 22,
                    height = 18,
                    offset = { x = 5, y = 7 }
                },
                health = {
                    health_percentage = 100
                },
                projectile_emitter = {
                    velocity = { x = 200, y = 0 },
                    duration = 2, -- seconds
                    repeat_frequency = 1, -- seconds
                    hit_percentage_damage = 10,
                    friendly = false
                }
            }
        },
        {
            -- Tank 28
            group = "enemies",
            components = {
                transform = {
                    position = { x = 1423, y = 835 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "tank-tiger-left-texture",
                    width = 32,
                    height = 32,
                    z_index = 3
                },
                boxcollider = {
                    width = 25,
                    height = 18,
                    offset = { x = 7, y = 7 }
                },
                health = {
                    health_percentage = 100
                },
                projectile_emitter = {
                    velocity = { x = -200, y = 0 },
                    duration = 1, -- seconds
                    repeat_frequency = 2, -- seconds
                    hit_percentage_damage = 10,
                    friendly = false
                }
            }
        },
        {
            -- Tank 29
            group = "enemies",
            components = {
                transform = {
                    position = { x = 1450, y = 300 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "tank-tiger-down-texture",
                    width = 32,
                    height = 32,
                    z_index = 3
                },
                boxcollider = {
                    width = 19,
                    height = 20,
                    offset = { x = 6, y = 7 }
                },
                health = {
                    health_percentage = 100
                },
                projectile_emitter = {
                    velocity = { x = 0, y = 300 },
                    duration = 1, -- seconds
                    repeat_frequency = 1, -- seconds
                    hit_percentage_damage = 10,
                    friendly = false
                }
            }
        },
        {
            -- Tank 30
            group = "enemies",
            components = {
                transform = {
                    position = { x = 195, y = 980 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "tank-tiger-up-texture",
                    width = 32,
                    height = 32,
                    z_index = 3
                },
                boxcollider = {
                    width = 18,
                    height = 25,
                    offset = { x = 7, y = 7 }
                },
                health = {
                    health_percentage = 100
                },
                projectile_emitter = {
                    velocity = { x = 0, y = -100 },
                    duration = 2, -- seconds
                    repeat_frequency = 1, -- seconds
                    hit_percentage_damage = 10,
                    friendly = false
                }
            }
        },
        {
            -- Tank 31
            group = "enemies",
            components = {
                transform = {
                    position = { x = 110, y = 1125 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "tank-panther-down-texture",
                    width = 32,
                    height = 32,
                    z_index = 3
                },
                boxcollider = {
                    width = 17,
                    height = 20,
                    offset = { x = 8, y = 4 }
                },
                health = {
                    health_percentage = 100
                },
                projectile_emitter = {
                    velocity = { x = 0, y = 300 },
                    duration = 1, -- seconds
                    repeat_frequency = 1, -- seconds
                    hit_percentage_damage = 10,
                    friendly = false
                }
            }
        },
        {
            -- Tank 32
            group = "enemies",
            components = {
                transform = {
                    position = { x = 1395, y = 540 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "tank-panther-killed-texture",
                    width = 32,
                    height = 32,
                    z_index = 3
                }
            }
        },
        {
            -- Truck 33
            group = "enemies",
            components = {
                transform = {
                    position = { x = 113, y = 580 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "truck-ford-down-texture",
                    width = 32,
                    height = 32,
                    z_index = 3
                },
                boxcollider = {
                    width = 12,
                    height = 25,
                    offset = { x = 10, y = 2 }
                },
                health = {
                    health_percentage = 100
                }
            }
        },
        {
            -- Truck 34
            group = "enemies",
            components = {
                transform = {
                    position = { x = 180, y = 1045 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "truck-ford-down-texture",
                    width = 32,
                    height = 32,
                    z_index = 3
                },
                boxcollider = {
                    width = 12,
                    height = 25,
                    offset = { x = 10, y = 2 }
                },
                health = {
                    health_percentage = 100
                }
            }
        },
        {
            -- Truck 35
            group = "enemies",
            components = {
                transform = {
                    position = { x = 195, y = 1055 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "truck-ford-down-texture",
                    width = 32,
                    height = 32,
                    z_index = 3
                },
                boxcollider = {
                    width = 12,
                    height = 25,
                    offset = { x = 10, y = 2 }
                },
                health = {
                    health_percentage = 100
                }
            }
        },
        {
            -- Truck 36
            group = "enemies",
            components = {
                transform = {
                    position = { x = 210, y = 1065 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "truck-ford-down-texture",
                    width = 32,
                    height = 32,
                    z_index = 3
                },
                boxcollider = {
                    width = 12,
                    height = 25,
                    offset = { x = 10, y = 2 }
                },
                health = {
                    health_percentage = 100
                }
            }
        },
        {
            -- Truck 37
            group = "enemies",
            components = {
                transform = {
                    position = { x = 545, y = 660 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "truck-ford-down-texture",
                    width = 32,
                    height = 32,
                    z_index = 3
                },
                boxcollider = {
                    width = 12,
                    height = 25,
                    offset = { x = 10, y = 2 }
                },
                health = {
                    health_percentage = 100
                }
            }
        },
        {
            -- Truck 38
            group = "enemies",
            components = {
                transform = {
                    position = { x = 560, y = 670 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "truck-ford-down-texture",
                    width = 32,
                    height = 32,
                    z_index = 3
                },
                boxcollider = {
                    width = 12,
                    height = 25,
                    offset = { x = 10, y = 2 }
                },
                health = {
                    health_percentage = 100
                }
            }
        },
        {
            -- Truck 39
            group = "enemies",
            components = {
                transform = {
                    position = { x = 1360, y = 880 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "truck-ford-up-texture",
                    width = 32,
                    height = 32,
                    z_index = 3
                },
                boxcollider = {
                    width = 12,
                    height = 20,
                    offset = { x = 10, y = 8 }
                },
                health = {
                    health_percentage = 100
                }
            }
        },
        {
            -- Truck 40
            group = "enemies",
            components = {
                transform = {
                    position = { x = 1380, y = 880 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "truck-ford-up-texture",
                    width = 32,
                    height = 32,
                    z_index = 3
                },
                boxcollider = {
                    width = 12,
                    height = 20,
                    offset = { x = 10, y = 8 }
                },
                health = {
                    health_percentage = 100
                }
            }
        },
        {
            -- Truck 41
            group = "enemies",
            components = {
                transform = {
                    position = { x = 1400, y = 880 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "truck-ford-up-texture",
                    width = 32,
                    height = 32,
                    z_index = 3
                },
                boxcollider = {
                    width = 12,
                    height = 20,
                    offset = { x = 10, y = 8 }
                },
                health = {
                    health_percentage = 100
                }
            }
        },
        {
            -- Truck 42
            group = "enemies",
            components = {
                transform = {
                    position = { x = 1505, y = 780 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "truck-ford-left-texture",
                    width = 32,
                    height = 32,
                    z_index = 3
                },
                boxcollider = {
                    width = 25,
                    height = 16,
                    offset = { x = 3, y = 10 }
                },
                health = {
                    health_percentage = 100
                }
            }
        },
        {
            -- Truck 43
            group = "enemies",
            components = {
                transform = {
                    position = { x = 1515, y = 790 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "truck-ford-left-texture",
                    width = 32,
                    height = 32,
                    z_index = 3
                },
                boxcollider = {
                    width = 25,
                    height = 16,
                    offset = { x = 3, y = 10 }
                },
                health = {
                    health_percentage = 100
                }
            }
        },
        {
            -- SAM Tank 44
            group = "enemies",
            components = {
                transform = {
                    position = { x = 495, y = 380 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "sam-tank-left-texture",
                    width = 32,
                    height = 32,
                    z_index = 3
                },
                animation = {
                    num_frames = 2,
                    speed_rate = 20 -- fps
                },
                boxcollider = {
                    width = 17,
                    height = 15,
                    offset = { x = 8, y = 8 }
                },
                health = {
                    health_percentage = 100
                },
                projectile_emitter = {
                    velocity = { x = -50, y = -50 },
                    duration = 3, -- seconds
                    repeat_frequency = 2, -- seconds
                    hit_percentage_damage = 5,
                    friendly = false
                }
            }
        },
        {
            -- SAM Tank 45
            group = "enemies",
            components = {
                transform = {
                    position = { x = 495, y = 410 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "sam-tank-left-texture",
                    width = 32,
                    height = 32,
                    z_index = 3
                },
                animation = {
                    num_frames = 2,
                    speed_rate = 20 -- fps
                },
                boxcollider = {
                    width = 17,
                    height = 15,
                    offset = { x = 8, y = 8 }
                },
                health = {
                    health_percentage = 100
                },
                projectile_emitter = {
                    velocity = { x = -50, y = -50 },
                    duration = 3, -- seconds
                    repeat_frequency = 2, -- seconds
                    hit_percentage_damage = 5,
                    friendly = false
                }
            }
        },
        {
            -- SAM Tank 46
            group = "enemies",
            components = {
                transform = {
                    position = { x = 1290, y = 115 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "sam-tank-left-texture",
                    width = 32,
                    height = 32,
                    z_index = 3
                },
                animation = {
                    num_frames = 2,
                    speed_rate = 20 -- fps
                },
                boxcollider = {
                    width = 17,
                    height = 15,
                    offset = { x = 8, y = 8 }
                },
                health = {
                    health_percentage = 100
                },
                projectile_emitter = {
                    velocity = { x = -100, y = -75 },
                    duration = 2, -- seconds
                    repeat_frequency = 2, -- seconds
                    hit_percentage_damage = 5,
                    friendly = false
                }
            }
        },
        {
            -- SAM Tank 47
            group = "enemies",
            components = {
                transform = {
                    position = { x = 935, y = 557 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "sam-tank-left-texture",
                    width = 32,
                    height = 32,
                    z_index = 3
                },
                animation = {
                    num_frames = 2,
                    speed_rate = 20 -- fps
                },
                boxcollider = {
                    width = 17,
                    height = 15,
                    offset = { x = 8, y = 8 }
                },
                health = {
                    health_percentage = 100
                },
                projectile_emitter = {
                    velocity = { x = -100, y = -60 },
                    duration = 2, -- seconds
                    repeat_frequency = 2, -- seconds
                    hit_percentage_damage = 5,
                    friendly = false
                }
            }
        },
        {
            -- SAM Truck 48
            group = "enemies",
            components = {
                transform = {
                    position = { x = 114, y = 700 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "sam-truck-right-texture",
                    width = 32,
                    height = 32,
                    z_index = 3
                },
                boxcollider = {
                    width = 17,
                    height = 15,
                    offset = { x = 8, y = 8 }
                },
                health = {
                    health_percentage = 100
                },
                projectile_emitter = {
                    velocity = { x = 50, y = -50 },
                    duration = 2, -- seconds
                    repeat_frequency = 1, -- seconds
                    hit_percentage_damage = 5,
                    friendly = false
                }
            }
        },
        {
            -- SAM Truck 49
            group = "enemies",
            components = {
                transform = {
                    position = { x = 114, y = 720 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "sam-truck-right-texture",
                    width = 32,
                    height = 32,
                    z_index = 3
                },
                boxcollider = {
                    width = 17,
                    height = 15,
                    offset = { x = 8, y = 8 }
                },
                health = {
                    health_percentage = 100
                },
                projectile_emitter = {
                    velocity = { x = 50, y = -50 },
                    duration = 2, -- seconds
                    repeat_frequency = 1, -- seconds
                    hit_percentage_damage = 5,
                    friendly = false
                }
            }
        },
        {
            -- SAM Truck 5
            group = "enemies",
            components = {
                transform = {
                    position = { x = 116, y = 499 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "sam-truck-right-texture",
                    width = 32,
                    height = 32,
                    z_index = 3
                },
                boxcollider = {
                    width = 17,
                    height = 15,
                    offset = { x = 8, y = 8 }
                },
                health = {
                    health_percentage = 100
                },
                projectile_emitter = {
                    velocity = { x = 50, y = -70 },
                    duration = 2, -- seconds
                    repeat_frequency = 1, -- seconds
                    hit_percentage_damage = 5,
                    friendly = false
                }
            }
        },
        {
            -- SAM Truck 51
            group = "enemies",
            components = {
                transform = {
                    position = { x = 1454, y = 215 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "sam-truck-right-texture",
                    width = 32,
                    height = 32,
                    z_index = 3
                },
                boxcollider = {
                    width = 17,
                    height = 15,
                    offset = { x = 8, y = 8 }
                },
                health = {
                    health_percentage = 100
                },
                projectile_emitter = {
                    velocity = { x = 50, y = -70 },
                    duration = 2, -- seconds
                    repeat_frequency = 1, -- seconds
                    hit_percentage_damage = 5,
                    friendly = false
                }
            }
        },
        {
            -- SAM Truck 52
            group = "enemies",
            components = {
                transform = {
                    position = { x = 1454, y = 231 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "sam-truck-right-texture",
                    width = 32,
                    height = 32,
                    z_index = 3
                },
                boxcollider = {
                    width = 17,
                    height = 15,
                    offset = { x = 8, y = 8 }
                },
                health = {
                    health_percentage = 100
                },
                projectile_emitter = {
                    velocity = { x = 50, y = -70 },
                    duration = 2, -- seconds
                    repeat_frequency = 1, -- seconds
                    hit_percentage_damage = 5,
                    friendly = false
                }
            }
        },
        {
            -- SAM Truck 53
            group = "enemies",
            components = {
                transform = {
                    position = { x = 1454, y = 247 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "sam-truck-right-texture",
                    width = 32,
                    height = 32,
                    z_index = 3
                },
                boxcollider = {
                    width = 17,
                    height = 15,
                    offset = { x = 8, y = 8 }
                },
                health = {
                    health_percentage = 100
                },
                projectile_emitter = {
                    velocity = { x = 50, y = -70 },
                    duration = 2, -- seconds
                    repeat_frequency = 1, -- seconds
                    hit_percentage_damage = 5,
                    friendly = false
                }
            }
        },
        {
            -- Vegetation 54
            components = {
                transform = {
                    position = { x = 115, y = 633 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "tree5-texture",
                    width = 32,
                    height = 32,
                    z_index = 2
                },
            }
        },
        {
            -- Vegetation 55
            components = {
                transform = {
                    position = { x = 117, y = 650 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "tree5-texture",
                    width = 32,
                    height = 32,
                    z_index = 2
                },
            }
        },
        {
            -- Vegetation 56
            components = {
                transform = {
                    position = { x = 318, y = 490 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "tree6-texture",
                    width = 32,
                    height = 32,
                    z_index = 2
                },
            }
        },
        {
            -- Vegetation 57
            components = {
                transform = {
                    position = { x = 668, y = 526 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "tree14-texture",
                    width = 32,
                    height = 32,
                    z_index = 2
                },
            }
        },
        {
            -- Vegetation 58
            components = {
                transform = {
                    position = { x = 1018, y = 738 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "tree17-texture",
                    width = 17,
                    height = 20,
                    z_index = 2
                },
            }
        },
        {
            -- Vegetation 59
            components = {
                transform = {
                    position = { x = 1034, y = 738 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "tree17-texture",
                    width = 17,
                    height = 20,
                    z_index = 2
                },
            }
        },
        {
            -- Vegetation 60
            components = {
                transform = {
                    position = { x = 1028, y = 745 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "tree18-texture",
                    width = 17,
                    height = 20,
                    z_index = 2
                },
            }
        },
        {
            -- Vegetation 61
            components = {
                transform = {
                    position = { x = 1390, y = 440 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "tree10-texture",
                    width = 31,
                    height = 32,
                    z_index = 2
                },
            }
        },
        {
            -- Vegetation 62
            components = {
                transform = {
                    position = { x = 1400, y = 445 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "tree10-texture",
                    width = 31,
                    height = 32,
                    z_index = 2
                },
            }
        },
        {
            -- Vegetation 63
            components = {
                transform = {
                    position = { x = 1365, y = 290 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "tree14-texture",
                    width = 32,
                    height = 32,
                    z_index = 2
                },
            }
        },
        {
            -- Obstacles 64
            components = {
                transform = {
                    position = { x = 669, y = 549 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "obstacles7-texture",
                    width = 16,
                    height = 16,
                    z_index = 2
                },
            }
        },
        {
            -- Obstacles 65
            components = {
                transform = {
                    position = { x = 685, y = 549 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "obstacles7-texture",
                    width = 16,
                    height = 16,
                    z_index = 2
                },
            }
        },
        {
            -- Obstacles 66
            components = {
                transform = {
                    position = { x = 315, y = 505 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "obstacles7-texture",
                    width = 16,
                    height = 16,
                    z_index = 2
                },
            }
        },
        {
            -- Obstacles 67
            components = {
                transform = {
                    position = { x = 330, y = 507 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "obstacles7-texture",
                    width = 16,
                    height = 16,
                    z_index = 2
                },
            }
        },
        {
            -- Obstacles 68
            components = {
                transform = {
                    position = { x = 438, y = 390 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "obstacles7-texture",
                    width = 16,
                    height = 16,
                    z_index = 2
                },
            }
        },
        {
            -- Obstacles 69
            components = {
                transform = {
                    position = { x = 449, y = 408 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "obstacles7-texture",
                    width = 16,
                    height = 16,
                    z_index = 2
                },
            }
        },
        {
            -- Obstacles 70
            components = {
                transform = {
                    position = { x = 431, y = 416 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "obstacles7-texture",
                    width = 16,
                    height = 16,
                    z_index = 2
                },
            }
        },
        {
            -- Obstacles 71
            components = {
                transform = {
                    position = { x = 940, y = 695 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "obstacles7-texture",
                    width = 16,
                    height = 16,
                    z_index = 2
                },
            }
        },
        {
            -- Obstacles 72
            components = {
                transform = {
                    position = { x = 955, y = 705 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "obstacles7-texture",
                    width = 16,
                    height = 16,
                    z_index = 2
                },
            }
        },
        {
            -- Obstacles 73
            components = {
                transform = {
                    position = { x = 1085, y = 507 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "obstacles7-texture",
                    width = 16,
                    height = 16,
                    z_index = 2
                },
            }
        },
        {
            -- Obstacles 74
            components = {
                transform = {
                    position = { x = 1075, y = 527 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "obstacles7-texture",
                    width = 16,
                    height = 16,
                    z_index = 2
                },
            }
        },
        {
            -- Obstacles 75
            components = {
                transform = {
                    position = { x = 1075, y = 547 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "obstacles7-texture",
                    width = 16,
                    height = 16,
                    z_index = 2
                },
            }
        },
        {
            -- Obstacles 76
            components = {
                transform = {
                    position = { x = 1085, y = 567 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "obstacles7-texture",
                    width = 16,
                    height = 16,
                    z_index = 2
                },
            }
        },
        {
            -- Obstacles 77
            components = {
                transform = {
                    position = { x = 1355, y = 449 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "obstacles2-texture",
                    width = 32,
                    height = 32,
                    z_index = 2
                },
            }
        },
        {
            -- Obstacles 78
            components = {
                transform = {
                    position = { x = 1430, y = 446 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "obstacles2-texture",
                    width = 32,
                    height = 32,
                    z_index = 2
                },
            }
        },
        {
            -- Obstacles 79
            components = {
                transform = {
                    position = { x = 1435, y = 195 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "obstacles7-texture",
                    width = 16,
                    height = 16,
                    z_index = 2
                },
            }
        },
        {
            -- Obstacles 80
            components = {
                transform = {
                    position = { x = 1425, y = 215 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "obstacles7-texture",
                    width = 16,
                    height = 16,
                    z_index = 2
                },
            }
        },
        {
            -- Obstacles 81
            components = {
                transform = {
                    position = { x = 1425, y = 235 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "obstacles7-texture",
                    width = 16,
                    height = 16,
                    z_index = 2
                },
            }
        },
        {
            -- Obstacles 82
            components = {
                transform = {
                    position = { x = 1425, y = 255 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "obstacles7-texture",
                    width = 16,
                    height = 16,
                    z_index = 2
                },
            }
        },
        {
            -- Obstacles 83
            components = {
                transform = {
                    position = { x = 1435, y = 275 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "obstacles7-texture",
                    width = 16,
                    height = 16,
                    z_index = 2
                },
            }
        },
        {
            -- Obstacles 84
            components = {
                transform = {
                    position = { x = 1360, y = 310 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "obstacles7-texture",
                    width = 16,
                    height = 16,
                    z_index = 2
                },
            }
        },
        {
            -- Obstacles 85
            components = {
                transform = {
                    position = { x = 1380, y = 312 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "obstacles7-texture",
                    width = 16,
                    height = 16,
                    z_index = 2
                },
            }
        },
        {
            -- Obstacles 86
            components = {
                transform = {
                    position = { x = 1330, y = 212 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "obstacles1-texture",
                    width = 32,
                    height = 32,
                    z_index = 2
                },
            }
        },
        {
            -- Obstacles 87
            components = {
                transform = {
                    position = { x = 1360, y = 232 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "obstacles1-texture",
                    width = 32,
                    height = 32,
                    z_index = 2
                },
            }
        },
        {
            -- Army 88
            components = {
                transform = {
                    position = { x = 630, y = 405 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "army-walk-left-texture",
                    width = 32,
                    height = 32,
                    z_index = 1
                },
            }
        },
        {
            -- Army 89
            components = {
                transform = {
                    position = { x = 497, y = 450 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "army-walk-right-texture",
                    width = 32,
                    height = 32,
                    z_index = 1
                },
            }
        },
        {
            -- Army 90
            components = {
                transform = {
                    position = { x = 572, y = 560 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "army-gun-left-texture",
                    width = 32,
                    height = 32,
                    z_index = 1
                },
            }
        },
        {
            -- Army 91
            components = {
                transform = {
                    position = { x = 114, y = 980 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "army-walk-up-texture",
                    width = 32,
                    height = 32,
                    z_index = 1
                },
            }
        },
        {
            -- Army 92
            components = {
                transform = {
                    position = { x = 114, y = 1030 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "army-walk-down-texture",
                    width = 32,
                    height = 32,
                    z_index = 1
                },
            }
        },
        {
            -- Army 93
            components = {
                transform = {
                    position = { x = 883, y = 490 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "army-walk-left-texture",
                    width = 32,
                    height = 32,
                    z_index = 1
                },
            }
        },
        {
            -- Army 94
            components = {
                transform = {
                    position = { x = 113, y = 851 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "army-gun-right-texture",
                    width = 32,
                    height = 32,
                    z_index = 1
                },
            }
        },
        {
            -- Army 95
            components = {
                transform = {
                    position = { x = 750, y = 630 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "army-walk-left-texture",
                    width = 32,
                    height = 32,
                    z_index = 1
                },
            }
        },
        {
            -- Army 96
            components = {
                transform = {
                    position = { x = 800, y = 630 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "army-walk-right-texture",
                    width = 32,
                    height = 32,
                    z_index = 1
                },
            }
        },
        {
            -- Army 97
            components = {
                transform = {
                    position = { x = 856, y = 115 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "army-gun-down-texture",
                    width = 32,
                    height = 32,
                    z_index = 1
                },
            }
        },
        {
            -- Army 98
            components = {
                transform = {
                    position = { x = 900, y = 115 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "army-gun-up-texture",
                    width = 32,
                    height = 32,
                    z_index = 1
                },
            }
        },
        {
            -- Army 99
            components = {
                transform = {
                    position = { x = 1117, y = 530 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "army-walk-right-texture",
                    width = 32,
                    height = 32,
                    z_index = 1
                },
            }
        },
        {
            -- Army 100
            components = {
                transform = {
                    position = { x = 755, y = 440 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "army-gun-down-texture",
                    width = 32,
                    height = 32,
                    z_index = 1
                },
            }
        },
        {
            -- Army 101
            components = {
                transform = {
                    position = { x = 810, y = 440 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "army-gun-down-texture",
                    width = 32,
                    height = 32,
                    z_index = 1
                },
            }
        },
        {
            -- Army 102
            components = {
                transform = {
                    position = { x = 1390, y = 690 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "army-walk-killed-texture",
                    width = 32,
                    height = 32,
                    z_index = 1
                },
            }
        },
        {
            -- Army 103
            components = {
                transform = {
                    position = { x = 1425, y = 690 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "army-walk-killed-texture",
                    width = 32,
                    height = 32,
                    z_index = 1
                },
            }
        },
        {
            -- Army 104
            components = {
                transform = {
                    position = { x = 1465, y = 690 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "army-walk-killed-texture",
                    width = 32,
                    height = 32,
                    z_index = 1
                },
            }
        },
        {
            -- Boat 105
            components = {
                transform = {
                    position = { x = 80, y = 520 },
                    scale = { x = 0.8, y = 0.8 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "boat-texture",
                    width = 21,
                    height = 126,
                    z_index = 1
                },
            }
        },
        {
            -- Boat 106
            components = {
                transform = {
                    position = { x = 80, y = 790 },
                    scale = { x = 0.8, y = 0.8 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "boat-texture",
                    width = 21,
                    height = 126,
                    z_index = 1
                },
            }
        },
        {
            -- Boat 107
            components = {
                transform = {
                    position = { x = 345, y = 423 },
                    scale = { x = 0.8, y = 0.8 },
                    rotation = 270.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "boat-texture",
                    width = 21,
                    height = 126,
                    z_index = 1
                },
            }
        },
        {
            -- Boat 108
            components = {
                transform = {
                    position = { x = 1510, y = 460 },
                    scale = { x = 0.8, y = 0.8 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "boat-texture",
                    width = 21,
                    height = 126,
                    z_index = 1
                },
            }
        },
        {
            -- Carrier 109
            components = {
                transform = {
                    position = { x = 670, y = 150 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "carrier-texture",
                    width = 59,
                    height = 191,
                    z_index = 1
                },
            }
        },
        {
            -- Carrier 110
            components = {
                transform = {
                    position = { x = 300, y = 975 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "carrier-texture",
                    width = 59,
                    height = 191,
                    z_index = 1
                },
            }
        },
        {
            -- F-22 fighter jet  111
            group = "enemies",
            components = {
                transform = {
                    position = { x = 688, y = 165 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "f22-texture",
                    width = 32,
                    height = 32,
                    z_index = 4
                },
                animation = {
                    num_frames = 2,
                    speed_rate = 10 -- fps
                },
                boxcollider = {
                    width = 20,
                    height = 25,
                    offset = { x = 5, y = 5}
                },
                health = {
                    health_percentage = 100
                }
            }
        },
        {
            -- SU-27 fighter jet  112
            group = "enemies",
            components = {
                transform = {
                    position = { x = 685, y = 300 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = -10.0, -- degrees
                },
                rigidbody = {
                    velocity = { x = -5.5 , y = -35.0 }
                },
                sprite = {
                    texture_asset_id = "su27-texture",
                    width = 32,
                    height = 32,
                    z_index = 5
                },
                animation = {
                    num_frames = 2,
                    speed_rate = 10 -- fps
                },
                boxcollider = {
                    width = 25,
                    height = 30,
                    offset = { x = 5, y = 0 }
                },
                health = {
                    health_percentage = 100
                }
            }
        },
        {
            -- Bomber plane 113
            group = "enemies",
            components = {
                transform = {
                    position = { x = 464, y = 520 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "bomber-texture",
                    width = 32,
                    height = 32,
                    z_index = 5
                },
                animation = {
                    num_frames = 2,
                    speed_rate = 10 -- fps
                },
                boxcollider = {
                    width = 32,
                    height = 32,
                    offset = { x = 0, y = 0 }
                },
                health = {
                    health_percentage = 100
                }
            }
        },
        {
            -- FW190 plane 114
            group = "enemies",
            components = {
                transform = {
                    position = { x = 1000, y = 143 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = -90.0, -- degrees
                },
                rigidbody = {
                    velocity = { x = -50.0, y = 0.0 }
                },
                sprite = {
                    texture_asset_id = "fw190-texture",
                    width = 32,
                    height = 32,
                    z_index = 6
                },
                animation = {
                    num_frames = 3,
                    speed_rate = 15 -- fps
                },
                boxcollider = {
                    width = 32,
                    height = 30,
                    offset = { x = 0, y = 0 }
                },
                health = {
                    health_percentage = 100
                }
            }
        },
        {
            -- UPF7 plane 115
            group = "enemies",
            components = {
                transform = {
                    position = { x = 920, y = 179 },
                    scale = { x = 0.8, y = 0.8 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "upf7-texture",
                    width = 32,
                    height = 32,
                    z_index = 5
                },
                animation = {
                    num_frames = 2,
                    speed_rate = 10 -- fps
                }
            }
        },
        {
            -- UPF7 plane 116
            group = "enemies",
            components = {
                transform = {
                    position = { x = 950, y = 179 },
                    scale = { x = 0.8, y = 0.8 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "upf7-texture",
                    width = 32,
                    height = 32,
                    z_index = 5
                },
                animation = {
                    num_frames = 2,
                    speed_rate = 10 -- fps
                }
            }
        },
        {
            -- UPF7 plane 117
            group = "enemies",
            components = {
                transform = {
                    position = { x = 980, y = 179 },
                    scale = { x = 0.8, y = 0.8 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "upf7-texture",
                    width = 32,
                    height = 32,
                    z_index = 5
                },
                animation = {
                    num_frames = 2,
                    speed_rate = 10 -- fps
                }
            }
        },
        {
            -- SU-27 fighter jet 118
            group = "enemies",
            components = {
                transform = {
                    position = { x = 317, y = 985 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                rigidbody = {
                    velocity = { x = 0.0, y = -50.0 }
                },
                sprite = {
                    texture_asset_id = "su27-texture",
                    width = 32,
                    height = 32,
                    z_index = 3
                },
                animation = {
                    num_frames = 2,
                    speed_rate = 10 -- fps
                },
                boxcollider = {
                    width = 32,
                    height = 32
                },
                health = {
                    health_percentage = 100
                },
                projectile_emitter = {
                    velocity = { x = 0, y = -100 },
                    duration = 2, -- seconds
                    repeat_frequency = 1, -- seconds
                    hit_percentage_damage = 10,
                    friendly = false
                },
                on_update_script = {
                    [0] =
                    function(entity, delta_time, ellapsed_time)
                        --print("Executing the SU-27 fighter jet Lua script!")
                        -- this function makes the fighter jet move up and down the map shooting projectiles
                        local current_position_x, current_position_y = get_position(entity)
                        local current_velocity_x, current_velocity_y = get_velocity(entity)

                        -- if it reaches the top or the bottom of the map
                        if current_position_y < 10  or current_position_y > map_height - 32 then
                            set_velocity(entity, 0, current_velocity_y * -1); -- flip the entity y-velocity
                        else
                            set_velocity(entity, 0, current_velocity_y); -- do not flip y-velocity
                        end

                        -- set the transform rotation to match going up or down
                        if (current_velocity_y < 0) then
                            set_rotation(entity, 0) -- point up
                            set_velocity(entity, 0, -200) -- shoot projectiles up
                        else
                            set_rotation(entity, 180) -- point down
                            set_velocity(entity, 0, 200) -- shoot projectiles down
                        end
                    end
                }
            }
        },
        {
            -- F-22 fighter jet 119
            group = "enemies",
            components = {
                transform = {
                    position = { x = 10, y = 10 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 90.0, -- degrees
                },
                rigidbody = {
                    velocity = { x = 0.0, y = 0.0 }
                },
                sprite = {
                    texture_asset_id = "f22-texture",
                    width = 32,
                    height = 32,
                    z_index = 3
                },
                animation = {
                    num_frames = 2,
                    speed_rate = 10 -- fps
                },
                boxcollider = {
                    width = 32,
                    height = 32
                },
                health = {
                    health_percentage = 100
                },
                projectile_emitter = {
                    velocity = { x = 200, y = 0 },
                    duration = 1, -- secondsm
                    repeat_frequency = 1, -- seconds
                    hit_percentage_damage = 10,
                    friendly = false
                },
                on_update_script = {
                    [0] =
                    function(entity, delta_time, ellapsed_time)
                        --print("Executing F-22 Lua script!")
                        -- change the position of the the airplane to follow a sine wave movement
                        local current_position_x, current_position_y = get_position(entity)
                        local speed = 90.0
                        local new_x = current_position_x + delta_time * speed
                        local new_y = 100 + math.sin(ellapsed_time * 0.9) * 50
                        set_position(entity, new_x, new_y) -- set the new position
                    end
                }
            }
        }
    }
}

-- Define some useful global variables
map_width = Level.tilemap.num_cols * Level.tilemap.tile_size * Level.tilemap.scale
map_height = Level.tilemap.num_rows * Level.tilemap.tile_size * Level.tilemap.scale
