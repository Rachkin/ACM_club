-- Sample room

function enter()
    room = {  }
    room["background"] = "back"
    room["say"]        = "muda"
    room["characters"] = {"giorno"}
    room["speaker"]    = "giorno"
    return room
end

function next(variant)
    glob_sets(0, "muda")
    return "sample" -- next file is sample.lua
end