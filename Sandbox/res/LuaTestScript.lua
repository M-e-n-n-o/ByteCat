function onAttach()
	LOG_INFO("attach")
end

local rad = math.rad

function onUpdate(delta)
	local speed = 15.0
	local rotationSpeed = 60.0

	local currentSpeed = 0.0
	local currentRotationSpeed = 0.0

	pos = Get("position")
	local rot = Get("rotation")

	if (IsKeyPressed("W")) then
		currentSpeed = currentSpeed + speed
	end

	if (IsKeyPressed("S")) then
		currentSpeed = currentSpeed - speed
	end

	if (IsKeyPressed("D")) then
		currentRotationSpeed = currentRotationSpeed + rotationSpeed
	end

	if (IsKeyPressed("A")) then
		currentRotationSpeed = currentRotationSpeed - rotationSpeed
	end

	if (IsKeyPressed("Space")) then
		pos.y = pos.y + (speed * delta)
	end

	if (IsKeyPressed("LeftControl")) then
		pos.y = pos.y - (speed * delta)
	end

	rot.y = rot.y + (currentRotationSpeed * delta)

	local distance = currentSpeed * delta
	local y = rot.y + 270
	local dx = distance * math.cos(rad(y))
	local dz = distance * math.sin(rad(y))

	pos.x = pos.x + dx
	pos.z = pos.z + dz

	Set("position", pos)
	Set("rotation", rot)
end

function onDetach()
	LOG_INFO("detach")
end