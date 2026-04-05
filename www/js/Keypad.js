import ComponentBase from "./ComponentBase.js";

export default class Keypad extends ComponentBase {
    #keyIndex = undefined;
    #keyCount;

    constructor(cmodule, rows, cols, dataSuffix) {
        super(cmodule, `Keypad/${JSON.stringify([rows, cols])}`)
        this.#keyCount = rows.length * cols.length
        this.mapNodes('pad', dataSuffix, (node, attrVal) => {
            const index = parseInt(attrVal)

            if(index===NaN || index < 0 || index >= this.#keyCount) {
                console.warn(`Attribute 'data-pad' is Nan or not in [0..${this.#keyCount}[ for element ${node}`)
                return
            }
            const keypad = this
            node.addEventListener('mousedown', _ => keypad.setPressedKeyIndex(index))
            node.addEventListener('mouseup'  , _ => keypad.setPressedKeyIndex(undefined))
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