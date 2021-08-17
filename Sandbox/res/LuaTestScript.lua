function onAttach()
	print("attach")
end


function onUpdate(a)
	print("delta is " .. a)
end

function onDetach()
	print("detach")
end
