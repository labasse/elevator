import AnalogIO from "./AnalogIO.js"

export default class ResistorLadderPushBtns extends AnalogIO {
    #pin
    #pullup
    
    constructor(cmodule, pin, pullup_resistor, dataAttrSuffix=undefined) {
        super(cmodule, pin)
        this.#pin = pin
        this.#pullup = pullup_resistor
        this.mapNodes('r', dataAttrSuffix, (e, attrVal) => {
            e.addEventListener('mousedown', _ => this.resistor(parseInt(attrVal))),
            e.addEventListener('mouseup'  , _ => this.none())
        })
        this.none()
    }
    resistor(r) {
        this.set(this.#pin, Math.floor((this.max() * r)/(r + this.#pullup)))
    }
    none() {
        this.set(this.#pin, this.max())
    }
}
