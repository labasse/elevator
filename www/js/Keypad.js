export default class Keypad 
{
    #cmodule;
    #keyIndex = undefined;
    #keyCount;

    constructor(cmodule, rows, cols, dataSuffix) {
        const id = JSON.stringify([rows, cols])
        const dataAttr = dataSuffix ? `data-Keypad-${dataSuffix}` : 'data-Keypad'

        cmodule.Keypad ??= {}
        cmodule.Keypad[id] = this

        this.#cmodule = cmodule
        this.#keyCount = rows.length * cols.length
        document.querySelectorAll(`*[${dataAttr}]`).forEach(node => {
            const index = parseInt(node.getAttribute(dataAttr))

            if(index===NaN || index < 0 || index >= this.#keyCount) {
                console.warn(`Bad '${dataAttr}' for element ${node}`)
                return
            }
            node.addEventListener('mousedown', _ => this.#cmodule.Keypad[id].setPressedKeyIndex(index))
            node.addEventListener('mouseup'  , _ => this.#cmodule.Keypad[id].setPressedKeyIndex(undefined))
        })
    }
    setPressedKeyIndex(index) {
        if(index<0 || index>=this.#keyCount) {
            throw new RangeError("Pressed key index out of bound")
        }
        console.debug(index===undefined 
            ? `Keypad: ${this.#keyIndex} released` 
            : `Keypad: ${index} pressed`
        )
        this.#keyIndex = index
    }
    getPressedKeyIndex() {
        return this.#keyIndex
    }
}