export default function makeDraggable(selector) {
    const div = document.querySelector('.panel')

    div.addEventListener('mousedown', e => {
        e.preventDefault()

        const r = div.getBoundingClientRect()
        const parentR = div.parentElement.getBoundingClientRect()
        const ox = parentR.left + e.clientX - r.left
        const oy = parentR.top  + e.clientY - r.top
        const move = e => {
            div.style.left = `${e.clientX - ox}px`
            div.style.top  = `${e.clientY - oy}px`
        }
        document.addEventListener('mousemove', move)
        document.addEventListener('mouseup', () =>
            document.removeEventListener('mousemove', move), { once: true }
        )
    })
}