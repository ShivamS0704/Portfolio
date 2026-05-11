window.addEventListener("load", () => {
  const preloader = document.getElementById("preloader");
  const percent = document.getElementById("preloaderPercent");
  const bar = document.getElementById("preloaderBar");
  const hamburger = document.getElementById("hamburger");
  const navLinks = document.getElementById("navLinks");
  const typedText = document.getElementById("typedText");
  const backTop = document.getElementById("backTop");
  const progress = document.getElementById("scrollProgress");
  const navbar = document.getElementById("navbar");
  const themeToggle = document.getElementById("themeToggle");

  if (preloader) {
    let load = 0;
    const loading = setInterval(() => {
      load++;
      if (percent) percent.textContent = load + "%";
      if (bar) bar.style.width = load + "%";

      if (load >= 100) {
        clearInterval(loading);
        setTimeout(() => {
          preloader.style.opacity = "0";
          preloader.style.visibility = "hidden";
          preloader.style.display = "none";
        }, 300);
      }
    }, 12);
  }

  const words = [
    "C Programmer",
    "Future Software Engineer",
    "Problem Solver",
    "Tech Enthusiast"
  ];

  let wordIndex = 0;
  let charIndex = 0;
  let deleting = false;

  function typeEffect() {
    if (!typedText) return;

    const currentWord = words[wordIndex];

    if (!deleting) {
      typedText.textContent = currentWord.substring(0, charIndex++);

      if (charIndex > currentWord.length) {
        deleting = true;
        setTimeout(typeEffect, 1200);
        return;
      }
    } else {
      typedText.textContent = currentWord.substring(0, charIndex--);

      if (charIndex < 0) {
        deleting = false;
        wordIndex = (wordIndex + 1) % words.length;
      }
    }

    setTimeout(typeEffect, deleting ? 50 : 100);
  }

  typeEffect();

  if (hamburger && navLinks) {
    hamburger.addEventListener("click", () => {
      hamburger.classList.toggle("active");
      hamburger.classList.toggle("open");
      navLinks.classList.toggle("active");
      navLinks.classList.toggle("open");
    });
  }

  document.querySelectorAll(".nav-link, .nav-links a").forEach(link => {
    link.addEventListener("click", () => {
      if (hamburger && navLinks) {
        hamburger.classList.remove("active", "open");
        navLinks.classList.remove("active", "open");
      }
    });
  });

  if (themeToggle) {
    if (localStorage.getItem("theme") === "light") {
      document.body.classList.add("light-mode");
      themeToggle.innerHTML = "<i class='bx bx-sun'></i>";
    }

    themeToggle.addEventListener("click", () => {
      document.body.classList.toggle("light-mode");

      if (document.body.classList.contains("light-mode")) {
        localStorage.setItem("theme", "light");
        themeToggle.innerHTML = "<i class='bx bx-sun'></i>";
      } else {
        localStorage.setItem("theme", "dark");
        themeToggle.innerHTML = "<i class='bx bx-moon'></i>";
      }
    });
  }

  function fixProjectButtons() {
    const projectCards = document.querySelectorAll(".project-card");

    projectCards.forEach(card => {
      const title = card.querySelector("h3, .project-title")?.textContent.trim().toLowerCase() || "";
      const buttons = card.querySelectorAll("a");

      buttons.forEach(button => {
        const text = button.textContent.trim().toLowerCase();

        if (text.includes("demo") && (title.includes("calculator") || title.includes("library") || title.includes("4-bit") || title.includes("adder") || title.includes("li-fi") || title.includes("lifi"))) {
          button.remove();
          return;
        }

        if (text.includes("code")) {
          button.setAttribute("target", "_blank");
          button.setAttribute("rel", "noopener noreferrer");

          if (title.includes("calculator")) {
            button.href = "calculator.c";
          } else if (title.includes("library")) {
            button.href = "library.c";
          } else if (title.includes("energy theft") || title.includes("smart energy")) {
            button.href = "energy-theft-detection.py";
          }
        }
      });
    });
  }

  function fixCertificateButtons() {
    document.querySelectorAll(".cert-card, .certificate-card").forEach(card => {
      const text = card.textContent.toLowerCase();
      const button = card.querySelector("a");
      if (!button) return;

      button.setAttribute("target", "_blank");
      button.setAttribute("rel", "noopener noreferrer");

      if (text.includes("six sigma")) {
        button.href = "six sigma.pdf";
      }

      if (text.includes("arduino")) {
        button.href = "arduino course certificate.pdf";
      }
    });
  }

  function fixContactForm() {
    const form = document.getElementById("contactForm");
    if (!form) return;

    form.setAttribute("action", "https://formspree.io/f/xeenvdvo");
    form.setAttribute("method", "POST");

    const nameInput = document.getElementById("fname");
    const emailInput = document.getElementById("femail");
    const subjectInput = document.getElementById("fsubject");
    const messageInput = document.getElementById("fmessage");

    if (nameInput) nameInput.setAttribute("name", "name");
    if (emailInput) emailInput.setAttribute("name", "email");
    if (subjectInput) subjectInput.setAttribute("name", "subject");
    if (messageInput) messageInput.setAttribute("name", "message");

    if (!form.querySelector("input[name='_subject']")) {
      const hiddenSubject = document.createElement("input");
      hiddenSubject.type = "hidden";
      hiddenSubject.name = "_subject";
      hiddenSubject.value = "New message from Shivam Sharma Portfolio";
      form.prepend(hiddenSubject);
    }
  }

  fixProjectButtons();
  fixCertificateButtons();
  fixContactForm();

  function revealOnScroll() {
    document
      .querySelectorAll(".reveal, .reveal-up, .reveal-left, .reveal-right, .section, .skill-card, .project-card, .cert-card, .edu-item")
      .forEach(item => {
        if (item.getBoundingClientRect().top < window.innerHeight - 80) {
          item.classList.add("show", "visible");
          item.style.opacity = "1";
          item.style.visibility = "visible";
        }
      });
  }

  function handleScroll() {
    const totalHeight = document.documentElement.scrollHeight - window.innerHeight;
    const progressHeight = totalHeight > 0 ? (window.scrollY / totalHeight) * 100 : 0;

    if (progress) progress.style.width = progressHeight + "%";
    if (navbar) navbar.classList.toggle("scrolled", window.scrollY > 50);
    if (backTop) backTop.classList.toggle("show", window.scrollY > 400);

    revealOnScroll();
  }

  window.addEventListener("scroll", handleScroll);
  handleScroll();
  revealOnScroll();

  if (backTop) {
    backTop.addEventListener("click", () => {
      window.scrollTo({ top: 0, behavior: "smooth" });
    });
  }
});