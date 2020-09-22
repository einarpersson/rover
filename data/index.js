const toggleBtn = document.getElementById("toggle-btn")

toggleBtn.addEventListener("click", (e) => {
    fetch('/toggle')
})
