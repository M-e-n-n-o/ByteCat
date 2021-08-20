function onAttach()
	LOG_INFO("attach")
end

function onUpdate(delta)
	local pos = Get("rotation")
	pos.y = pos.y + (delta * 100)
	Set("rotation", pos)
end

function onDetach()
	LOG_INFO("detach")
end