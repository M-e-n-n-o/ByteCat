function onAttach()
	LOG_INFO("attach")
end

function onUpdate(delta)
	local rotation = Get("rotation")

	rotation.z = rotation.z + (delta * 100)

	Set("rotation", rotation)
end

function onDetach()
	LOG_INFO("detach")
end