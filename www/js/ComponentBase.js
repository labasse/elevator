export default class ComponentBase {
    #cmodule
    #keyName

    constructor(cmodule, keyName) {
        this.#keyName = keyName
        this.#cmodule = cmodule
        this.#cmodule.wino ??= { }
        this.#cmodule.wino[this.#keyName] = this
    }
    cmodule() {
        return this.#cmodule
    }
    keyName() {
        return this.#keyName
    }
    mapNodes(dataAttrPrefix, dataAttrSuffix, action) {
        const dataAttr = this.dataAttribute(dataAttrPrefix, dataAttrSuffix)
     
        return Array.from(document.querySelectorAll(`*[${dataAttr}]`)).map(
            e => action(e, e.getAttribute(dataAttr))
        );
    }
    dataAttribute(dataAttrPrefix, dataAttrSuffix) {
        return dataAttrSuffix 
            ? `data-${dataAttrPrefix}-${dataAttrSuffix}` 
            : `data-${dataAttrPrefix}`;
    }
}