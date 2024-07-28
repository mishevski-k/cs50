const contactBtn = document.querySelector("#contact-btn");

if (contactBtn) {
    contactBtn.addEventListener("click", (event) => {
        event.preventDefault();

        const contactForm = document.querySelector("#contact-form");

        if (contactForm) {
            const formData = new FormData(contactForm);
            const formProps = Object.fromEntries(formData);
            console.log(contactForm.name.value);

            let string = `Name: ${contactForm.name.value} From: ${contactForm.companyName.value}\nEmail: ${contactForm.email.value}\nMessage: \n${contactForm.message.value}`

            alert(string);
        }
    })
}