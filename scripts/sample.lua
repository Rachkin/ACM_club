-- Sample room

function enter()
    room = {  }
    room["background"] = coridor1
    room["say"]        = "O my gad, Danilla you shto crazy?"
    room["characters"] = {neutral[sasha]}
    room["speaker"]    = name[sasha]
    return room
end

function next(variant)
    glob_sets(sasha, "muda")
    return "sample1" -- next file is sample.lua
end