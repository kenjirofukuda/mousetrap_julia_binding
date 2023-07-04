file = open("so.txt", "r")
content = readlines(file)

libs = String[]
for line in content
    m = match(r"=> .* \(", line)
    if !isnothing(m)
        push!(libs, m.match[4:end-2])
    end
end

#run(`mkdir bundle`)
for lib in libs
    run(`cp $lib bundle/`)
end