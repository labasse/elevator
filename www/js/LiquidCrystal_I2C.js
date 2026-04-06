import ComponentBase from './ComponentBase.js'

export default class LiquidCrystal_I2C extends ComponentBase {
    #lines = []
    #backlight

    constructor(cmodule, i2cAddr, dataAttrSuffix=undefined) {
        super(cmodule, `i2c/${i2cAddr}`)
        this.mapNodes('lcd-backlight', dataAttrSuffix, (e, attrVal) => {
            this.#backlight = { css: attrVal, node: e }
        })
        this.mapNodes('lcd-line', dataAttrSuffix, (e, attrVal) => {
            const line = parseInt(attrVal)

            if(line===NaN || line<0) {
                console.warn(`Attribute data-lcd-line must be a valid line number for ${e}`)
            }
            else {
                this.#lines[line] = e
            }
        })
    }
    backlight(on=true) {
        this.#backlight?.node.classList.toggle(this.#backlight.css, on)
    }
    line(index, text) {
        if(this.#lines[index]) {
            this.#lines[index].innerText = text
        }
        else {
            console.warn(`No paragraphe bound to line ${index} of ${this}`)
        }
    }
}