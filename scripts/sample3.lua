-- Sample1 room

function enter()
    room = {  }
    room["background"] = coridor2
    room["say"]        = "Hello"
    room["type"]       = "Game"
    room["characters"] = {happy[yana], neutral[sasha]}
    room["speaker"]    = name[sasha]
    return room
end

function next(variant)
    glob_sets(sasha, "muda")
    return "sample3" -- next file is sample.lua
end