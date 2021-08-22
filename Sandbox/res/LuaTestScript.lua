function onAttach()
	LOG_INFO("attach")
end

function onUpdate(delta)
	--pos = Get("position")
	--pos.y = 0
	--Set("position", pos)

	isPressed = Get("mouse", "Button1")

	if (isPressed) then
		LOG_INFO("Button1 is pressed")
	end
end

function onDetach()
	LOG_INFO("detach")
end