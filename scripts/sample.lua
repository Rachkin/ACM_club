-- Sample room

function enter()
    room = {  }
    room["background"] = coridor1
    room["say"]        = "О май гад, Данила, ты что крейзи?"
    room["characters"] = {neutral[sasha]}
    room["speaker"]    = name[sasha]
    return room
end

function next(variant)
    glob_sets(sasha, "muda")
    return "sample1" -- next file is sample.lua
end