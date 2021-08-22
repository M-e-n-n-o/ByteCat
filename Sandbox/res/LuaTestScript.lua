function onAttach()
	LOG_INFO("attach")
end


local rad = math.rad
local cos = math.cos
local sin = math.sin

local speed = 15.0
local rotationSpeed = 60

local currentSpeed, currentRotationSpeed = 0, 0
local Position, Rotation = {x = 0, y = 0, z = 0}

local KeyActions = {
    ["W"] = function(delta)
        currentSpeed = currentSpeed + speed
    end,
    ["S"] = function(delta)
        currentSpeed = currentSpeed - speed
    end,
    ["D"] = function(delta)
        currentRotationSpeed = currentRotationSpeed + rotationSpeed
    end,
    ["A"] = function(delta)
        currentRotationSpeed = currentRotationSpeed - rotationSpeed
    end,
    ["Space"] = function(delta)
        Position.y = Position.y + (speed * delta)
    end,
    ["LeftControl"] = function(delta)
        Position.y = Position.y - (speed * delta)
    end
}

function onUpdate(delta)
    currentSpeed, currentRotationSpeed = 0, 0
    Position, Rotation = Get("position"), Get("rotation")

    for key, func in pairs(KeyActions) do
        if IsKeyPressed(key) then
            func(delta)
        end
    end
    
    Rotation.y = Rotation.y + (currentRotationSpeed * delta)

    local distance = currentSpeed * delta
    local yRad = rad(Rotation.y + 270)
    
    local dx = distance * cos(yRad)
    local dz = distance * sin(yRad)
    
    Position.x = Position.x + dx
    Position.z = Position.z + dz
    
    Set("position", Position)
    Set("rotation", Rotation)
end


function onDetach()
	LOG_INFO("detach")
end