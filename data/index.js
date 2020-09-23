const forwardBtn = document.getElementById('forward-btn')
const backwardBtn = document.getElementById('backward-btn')
const stopBtn = document.getElementById('stop-btn')
const ledBtn = document.getElementById('led-btn')
const command = document.getElementById('command')

forwardBtn.addEventListener('click', async (e) => {
    command.textContent = 'FORWARD'
    
    try {
        const response = await fetch('/forward', {
            method: 'GET'
        })
        console.log(response.status, response.statusText)
    } catch (error) {
        console.error(error)
    }
})


backwardBtn.addEventListener('click', async (e) => {
    command.textContent = 'BACKWARD'
    
    try {
        const response = await fetch('/backward', {
            method: 'GET'
        })
        console.log(response.status, response.statusText)
    } catch (error) {
        console.error(error)
    }
})


stopBtn.addEventListener('click', async (e) => {
    command.textContent = 'STOP'

    try {
        const response = await fetch('/stop', {
            method: 'GET'
        })

        console.log(response.status, response.statusText)
    } catch (error) {
        console.error(error)
    }
})

ledBtn.addEventListener('click', async (e) => {
    try {
        const response = await fetch('/led', {
            method: 'GET'
        })

        console.log(response.status, response.statusText)
    } catch (error) {
        console.error(error)
    }
})
