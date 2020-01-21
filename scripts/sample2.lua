
function enter()
    room = {  }
    room["type"]        = "Homework"
    room["homework"]    = {}
    room["homework"][0] = {contest_id = 1286, letter = "A", name = "Girlyanda"}
    room["homework"][1] = {contest_id = 1286, letter = "B", name = "Ints on tree"}

    return room
end

function next(variant)
    glob_sets(sasha, "muda")
    return "sample3" -- next file is sample.lua
end